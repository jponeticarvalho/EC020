/*
 * Display_Ctrl.c
 *
 *  Created on: 03/04/2018
 *      Author: jpone
 */

#include "Display_Ctrl.h"

typedef enum enum_CommandState
{
	CMMD_WAIT = 0,
	CMMD_READING,
	CMMD_WRITETEMP,
	CMMD_WRITELIGHT,
} tenum_CommandState;

static tenum_CommandState enumCommandState;
static uint32_t uiSensorValue = 0;
volatile ttag_screenStrings tagScreenStrings;
static uint8_t ucWaitDrawn = 0;

void Display_Ctrl_Init(void)
{
	I2c_Ctrl_Init(); // Habilita o barramento I2C
	Ssp_Ctrl_Init(); //Habilita o barramento SPI
	Light_Ctrl_Init(); // Habilita o controlador do sensor de luz e define o rage de 0 a 4000
	Temp_Init(&Timer_getMsTimer); // habilita o sensor de temperatura ( o sensor de temperatura da placa funciona com base em tempo )
	Oled_Ctrl_Init(); // Habilita o display led
	Display_State_Init(); // Iniciliza o estdo da tela do display ( Waitng, Temp, Light )
	Button_Ctrl_Init(); // Habilita o controlador do botão

	strncpy((char*)tagScreenStrings.screenString_Line1,(const char*)"---------------",strlen((char*)"---------------"));
	strncpy((char*)tagScreenStrings.screenString_Line2,(const char*)"|    EC020:   |",strlen((char*)"|    EC020:   |"));
	strncpy((char*)tagScreenStrings.screenString_Line3,(const char*)"|Fer Avelar,  |",strlen((char*)"|Fer Avelar,  |"));
	strncpy((char*)tagScreenStrings.screenString_Line4,(const char*)"|Joao Pedro,  |",strlen((char*)"|Joao Pedro,  |"));
	strncpy((char*)tagScreenStrings.screenString_Line5,(const char*)"|Karla Carmo, |",strlen((char*)"|Karla Carmo, |"));
	strncpy((char*)tagScreenStrings.screenString_Line6,(const char*)"|Lucas Gaspar.|",strlen((char*)"|Lucas Gaspar.|"));
	strncpy((char*)tagScreenStrings.screenString_Line7,(const char*)"---------------",strlen((char*)"---------------"));

	Oled_Ctrl_ClearScreen(OLED_COLOR_BLACK); // Limpa o display
	Oled_Ctrl_PutScreen(tagScreenStrings, OLED_COLOR_WHITE, OLED_COLOR_BLACK); // escreve os nomes no display

	enumCommandState = CMMD_WAIT; // seta o estado da tela do display para witing ( nomes )
	uiSensorValue = 0; // seta o valor mostrado igual a 0

}

void Display_Ctrl_ProcessLoop() // Máquina de estado para do display
{
	ttagMessage tagMsg;
	portTickType blockTime = 20/portTICK_RATE_MS;

	while(1)
	{
		switch (enumCommandState) {
			case CMMD_WAIT:
				if(Display_State_Get() == DISPLAY_STATE_WAINTING) // Se o estado for Waiting
				{
					if(ucWaitDrawn == 0)
					{
						strncpy((char*)tagScreenStrings.screenString_Line1,(const char*)"---------------", 15);
						strncpy((char*)tagScreenStrings.screenString_Line2,(const char*)"|    EC020:   |", 15);
						strncpy((char*)tagScreenStrings.screenString_Line3,(const char*)"|Fer Avelar,  |", 15);
						strncpy((char*)tagScreenStrings.screenString_Line4,(const char*)"|Joao Pedro,  |", 15);
						strncpy((char*)tagScreenStrings.screenString_Line5,(const char*)"|Karla Carmo, |", 15);
						strncpy((char*)tagScreenStrings.screenString_Line6,(const char*)"|Lucas Gaspar.|", 15);
						strncpy((char*)tagScreenStrings.screenString_Line7,(const char*)"---------------", 15);

						vPortEnterCritical();
						Oled_Ctrl_PutScreen(tagScreenStrings, OLED_COLOR_WHITE, OLED_COLOR_BLACK); // Desenha os nomes
						vPortExitCritical();

						ucWaitDrawn = 1;
					}
				}
				else // Se o estado não for waiting
				{
					enumCommandState = CMMD_READING; // muda o estado para reading
					ucWaitDrawn = 0;
				}
				break;

			case CMMD_READING:
				if(xQueueReceive(Display_Ctrl_queue, &tagMsg, blockTime) == pdTRUE)
				{
					uiSensorValue = tagMsg.ulPayload;
					if(Display_State_Get() == DISPLAY_STATE_LIGHT) // Se o estado da tela for light
					{
						enumCommandState = CMMD_WRITELIGHT; // Mudo o estado do display para escrever a lumunisidade
					}
					else if(Display_State_Get() == DISPLAY_STATE_TEMP)// Se o estado da tela for temp
					{
						enumCommandState = CMMD_WRITETEMP;// mudo o estado do display para escrever temperatura
					}
					else // se não estiver em nenhum desses estados
					{
						enumCommandState = CMMD_WAIT; // muda para waiting
					}
				}
				if(Display_State_Get() == DISPLAY_STATE_WAINTING)
				{
					enumCommandState = CMMD_WAIT;
				}
				break;

			case CMMD_WRITELIGHT:  // estado write light

				strncpy((char*)tagScreenStrings.screenString_Line1,(const char*)"---------------", 15);
				strncpy((char*)tagScreenStrings.screenString_Line2,(const char*)"|             |", 15);
				strncpy((char*)tagScreenStrings.screenString_Line3,(const char*)"|    Lumens   |", 15);
				strncpy((char*)tagScreenStrings.screenString_Line4,(const char*)"|      =      |", 15);
				sprintf((char*)tagScreenStrings.screenString_Line5,"|    %05d    |",(int)uiSensorValue); // coloca o valor com 5 casas do sensor de luminosidade na tela
				strncpy((char*)tagScreenStrings.screenString_Line6,(const char*)"|             |", 15);
				strncpy((char*)tagScreenStrings.screenString_Line7,(const char*)"---------------", 15);

				vPortEnterCritical();
				Oled_Ctrl_PutScreen(tagScreenStrings, OLED_COLOR_WHITE, OLED_COLOR_BLACK); // desenha a string com a lumininosidade no display
				vPortExitCritical();

				enumCommandState = CMMD_WAIT;// muda o state para waiting

				break;

			case CMMD_WRITETEMP: //estado write temperatura

				strncpy((char*)tagScreenStrings.screenString_Line1,(const char*)"---------------", 15);
				strncpy((char*)tagScreenStrings.screenString_Line2,(const char*)"|             |", 15);
				strncpy((char*)tagScreenStrings.screenString_Line3,(const char*)"| Temperatura |", 15);
				strncpy((char*)tagScreenStrings.screenString_Line4,(const char*)"|      =      |", 15);
				sprintf((char*)tagScreenStrings.screenString_Line5, "|    %5.2f    |",(float)uiSensorValue/10.0); // escreve o valor da temperatura na tela
				strncpy((char*)tagScreenStrings.screenString_Line6,(const char*)"|             |", 15);
				strncpy((char*)tagScreenStrings.screenString_Line7,(const char*)"---------------", 15);

				vPortEnterCritical();
				Oled_Ctrl_PutScreen(tagScreenStrings, OLED_COLOR_WHITE, OLED_COLOR_BLACK); //desenha a string com a temperatura na tela
				vPortExitCritical();

				enumCommandState = CMMD_WAIT; // muda o state para waiting

				break;

		}
		vTaskDelay(400/portTICK_RATE_MS);
	}
}
