/*
 * Display_State.c
 *
 *  Created on: 05/04/2018
 *      Author: jpone
 */

#include "Display_State.h"

volatile tenu_displayState enuDisplayState;
volatile uint32_t uiMaxValue2Temp = 100;
volatile uint32_t uiMaxValue2Light = 4000;

void Display_State_Init(void)
{
	enuDisplayState = DISPLAY_STATE_WAINTING;
}

void Display_State_IncrementState(void)
{
	if(enuDisplayState == DISPLAY_STATE_WAINTING)
		enuDisplayState = DISPLAY_STATE_LIGHT;

	else if(enuDisplayState == DISPLAY_STATE_LIGHT)
		enuDisplayState = DISPLAY_STATE_TEMP;

	else if(enuDisplayState == DISPLAY_STATE_TEMP)
		enuDisplayState = DISPLAY_STATE_WAINTING;
}

void Display_State_Set(tenu_displayState enuNewDisplayState)
{
	enuDisplayState = enuNewDisplayState;
}

tenu_displayState Display_State_Get()
{
	return enuDisplayState;
}

void Display_State_setMaxValue2Temp(uint32_t temp)
{
	uiMaxValue2Temp = temp;
}

uint32_t Display_State_getMaxValue2Temp()
{
	return uiMaxValue2Temp;
}

void Display_State_setMaxValue2Light(uint32_t light)
{
	uiMaxValue2Light = light;
}

uint32_t Display_State_getMaxValue2Light()
{
	return uiMaxValue2Light;
}
