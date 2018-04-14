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

void Display_Ctrl_Init(void)
{
	I2c_Ctrl_Init();
	Ssp_Ctrl_Init();
	Light_Ctrl_Init();
	Temp_Init(&Timer_getMsTimer);
	Oled_Ctrl_Init();
	Display_State_Init();
	Button_Ctrl_Init();

	strncpy((char*)tagScreenStrings.screenString_Line1,(const char*)"---------------",strlen((char*)"---------------"));
	strncpy((char*)tagScreenStrings.screenString_Line2,(const char*)"|    EC020:   |",strlen((char*)"|    EC020:   |"));
	strncpy((char*)tagScreenStrings.screenString_Line3,(const char*)"|Fer Avelar,  |",strlen((char*)"|Fer Avelar,  |"));
	strncpy((char*)tagScreenStrings.screenString_Line4,(const char*)"|Joao Pedro,  |",strlen((char*)"|Joao Pedro,  |"));
	strncpy((char*)tagScreenStrings.screenString_Line5,(const char*)"|Karla Carmo, |",strlen((char*)"|Karla Carmo, |"));
	strncpy((char*)tagScreenStrings.screenString_Line6,(const char*)"|Lucas Gaspar.|",strlen((char*)"|Lucas Gaspar.|"));
	strncpy((char*)tagScreenStrings.screenString_Line7,(const char*)"---------------",strlen((char*)"---------------"));

	Oled_Ctrl_ClearScreen(OLED_COLOR_BLACK);
	Oled_Ctrl_PutScreen(tagScreenStrings, OLED_COLOR_WHITE, OLED_COLOR_BLACK);

	enumCommandState = CMMD_WAIT;
	uiSensorValue = 0;

}

void Display_Ctrl_ProcessLoop()
{

	switch (enumCommandState) {
		case CMMD_WAIT:
			if(Button_Ctrl_GetValue() == FALSE)
			{
				Display_State_IncrementState();
			}
			if(Display_State_Get() == DISPLAY_STATE_WAINTING)
			{
				strncpy((char*)tagScreenStrings.screenString_Line1,(const char*)"---------------",strlen((char*)"---------------"));
				strncpy((char*)tagScreenStrings.screenString_Line2,(const char*)"|    EC020:   |",strlen((char*)"|    EC020:   |"));
				strncpy((char*)tagScreenStrings.screenString_Line3,(const char*)"|Fer Avelar,  |",strlen((char*)"|Fer Avelar,  |"));
				strncpy((char*)tagScreenStrings.screenString_Line4,(const char*)"|Joao Pedro,  |",strlen((char*)"|Joao Pedro,  |"));
				strncpy((char*)tagScreenStrings.screenString_Line5,(const char*)"|Karla Carmo, |",strlen((char*)"|Karla Carmo, |"));
				strncpy((char*)tagScreenStrings.screenString_Line6,(const char*)"|Lucas Gaspar.|",strlen((char*)"|Lucas Gaspar.|"));
				strncpy((char*)tagScreenStrings.screenString_Line7,(const char*)"---------------",strlen((char*)"---------------"));

				Oled_Ctrl_PutScreen(tagScreenStrings, OLED_COLOR_WHITE, OLED_COLOR_BLACK);
			}
			else
				enumCommandState = CMMD_READING;
			break;

		case CMMD_READING:
			if(Display_State_Get() == DISPLAY_STATE_LIGHT)
			{
				uiSensorValue = Light_Ctrl_Read();
				enumCommandState = CMMD_WRITELIGHT;
			}
			else if(Display_State_Get() == DISPLAY_STATE_TEMP)
			{
				uiSensorValue = Temp_Read();
				enumCommandState = CMMD_WRITETEMP;
			}
			else
			{
				enumCommandState = CMMD_WAIT;
			}
			break;

		case CMMD_WRITELIGHT:

			strncpy((char*)tagScreenStrings.screenString_Line1,(const char*)"---------------",strlen((char*)"---------------"));
			strncpy((char*)tagScreenStrings.screenString_Line2,(const char*)"|             |",strlen((char*)"|    EC020:   |"));
			strncpy((char*)tagScreenStrings.screenString_Line3,(const char*)"|    Lumens   |",strlen((char*)"|Fer Avelar,  |"));
			strncpy((char*)tagScreenStrings.screenString_Line4,(const char*)"|      =      |",strlen((char*)"|Joao Pedro,  |"));
			sprintf((char*)tagScreenStrings.screenString_Line5,"|    %05d    |",(int)uiSensorValue);
			strncpy((char*)tagScreenStrings.screenString_Line6,(const char*)"|             |",strlen((char*)"|Lucas Gaspar.|"));
			strncpy((char*)tagScreenStrings.screenString_Line7,(const char*)"---------------",strlen((char*)"---------------"));

			Oled_Ctrl_PutScreen(tagScreenStrings, OLED_COLOR_WHITE, OLED_COLOR_BLACK);

			enumCommandState = CMMD_WAIT;

			break;

		case CMMD_WRITETEMP:

			strncpy((char*)tagScreenStrings.screenString_Line1,(const char*)"---------------",strlen((char*)"---------------"));
			strncpy((char*)tagScreenStrings.screenString_Line2,(const char*)"|             |",strlen((char*)"|    EC020:   |"));
			strncpy((char*)tagScreenStrings.screenString_Line3,(const char*)"| Temperatura |",strlen((char*)"|Fer Avelar,  |"));
			strncpy((char*)tagScreenStrings.screenString_Line4,(const char*)"|      =      |",strlen((char*)"|Joao Pedro,  |"));
			sprintf((char*)tagScreenStrings.screenString_Line5, "|    %5.2f    |",(float)uiSensorValue/10.0);
			strncpy((char*)tagScreenStrings.screenString_Line6,(const char*)"|             |",strlen((char*)"|Lucas Gaspar.|"));
			strncpy((char*)tagScreenStrings.screenString_Line7,(const char*)"---------------",strlen((char*)"---------------"));

			Oled_Ctrl_PutScreen(tagScreenStrings, OLED_COLOR_WHITE, OLED_COLOR_BLACK);

			enumCommandState = CMMD_WAIT;

			break;

	}

}
