/*****************************************************************************
 *   A demo example using several of the peripherals on the base board
 *
 *   Copyright(C) 2010, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/

#include "Common.h"

#include "Usart_Ctrl/Command/Command.h"
#include "Display_Ctrl/Display_Ctrl.h"
#include "Timer/Timer.h"
#include "lpc17xx_clkpwr.h"
#include "EasyWeb_Ctrl/easyweb.h"

xQueueHandle Mqtt_queue;

void peripheralInit(void);
void TCPTask(void);

void buttonCallback(ttagMessage tagMsg);
void tempCallback(ttagMessage tagMsg);
void lightCallback(ttagMessage tagMsg);

int main (void)
{
	peripheralInit(); // Habilita o Clock no GPIO
	Timer_init();
	Display_Ctrl_Init(); // Habilita o controle do display
	command_Init(); // Inicializa o controle de protocolo
	EasyWeb_Ctrl_Init(); // inicializa a Web

	Button_Ctrl_setCallback(buttonCallback);
	Temp_setCallback(tempCallback);
	Light_Ctrl_setCallback(lightCallback);

	Display_Ctrl_queue = xQueueCreate(8, sizeof(ttagMessage));
	Http_server_queue  = xQueueCreate(10, sizeof(ttagMessage));
	Mqtt_queue 		   = xQueueCreate(10, sizeof(ttagMessage));

	xTaskCreate(Display_Ctrl_ProcessLoop, "DisplayLoop", 360, NULL, 1, NULL);
	xTaskCreate(command_ProcessLoop, "CommandLoop", 240, NULL, 1, NULL);
	xTaskCreate(EasyWeb_Ctrl_ProcessLoop, "EasyWebLoop", 240, NULL, 2, NULL);
	xTaskCreate(EasyWeb_Ctrl_UpdaterTask, "EasyWebUpdater", 128, NULL, 1, NULL);
	xTaskCreate(TCPTask, "TCPTask", 128, NULL, 4, NULL);
	xTaskCreate(Button_Ctrl_Task, "btnTask", 128, NULL, 1, NULL);
	xTaskCreate(Temp_Task, "tmpTask", 128, NULL, 1, NULL);
	xTaskCreate(Light_Ctrl_Task, "lgtTask", 128, NULL, 1, NULL);


//	while(1)
//	{
//		Display_Ctrl_ProcessLoop(); // Loop do display
//		command_ProcessLoop(); //  Loop do comando do protocolo da UART
//		EasyWeb_Ctrl_ProcessLoop(); // Loop da Easy Web
//	}

	vTaskStartScheduler();

	for(;;);
}

void TCPTask()
{

	while(1)
	{
		vTaskDelay(50);
		TCPClockHandler();  // Call TCP handler
	}

}

void peripheralInit(void)
{

	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCGPIO, ENABLE);// FUNÇÃO DA MCU QUE HABILITA O CLOCK NA GPIO

}

void buttonCallback(ttagMessage tagMsg)
{
	if(tagMsg.enuSource == SRC_BUT)
	{
		if (tagMsg.ulPayload == FALSE) {
			Display_State_IncrementState();
		}
	}
}

void tempCallback(ttagMessage tagMsg)
{
	if(tagMsg.enuSource == SRC_TEMP)
	{
		xQueueSendToBack(Http_server_queue, &tagMsg, 15);
		xQueueSendToBack(Mqtt_queue, &tagMsg, 15);

		if(Display_State_Get() == DISPLAY_STATE_TEMP)
			xQueueSendToBack(Display_Ctrl_queue, &tagMsg, 15);
	}
}

void lightCallback(ttagMessage tagMsg)
{
	if(tagMsg.enuSource == SRC_LIGHT)
	{
		xQueueSendToBack(Http_server_queue, &tagMsg, 15);
		xQueueSendToBack(Mqtt_queue, &tagMsg, 15);

		if(Display_State_Get() == DISPLAY_STATE_LIGHT)
			xQueueSendToBack(Display_Ctrl_queue, &tagMsg, 15);
	}
}

void mqttUpdaterTask(void* pvParameters)
{
	ttagMessage tagMsg;
	uint8_t ucBuffer;
	while(1)
	{
		if(xQueueReceive(Mqtt_queue, &tagMsg, 15) == pdTRUE)
		{
			switch (tagMsg.enuSource) {
				case SRC_LIGHT:
					sprintf(ucBuffer, "L/%d\n", (int)tagMsg.ulPayload);
					Usart_Ctrl_SendData(USARTx, ucBuffer, strlen(ucBuffer));
					break;
				case SRC_TEMP:
					sprintf(ucBuffer, "T/%lf\n", (double)tagMsg.ulPayload/10.0);
					Usart_Ctrl_SendData(USARTx, ucBuffer, strlen(ucBuffer));
					break;
				default:
					break;
			}
		}
	}
}

//Parte obrigatoria para o FreeRtos

/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* This example does not use the idle hook to perform any processing. */
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This example does not use the tick hook to perform any processing. */
}
