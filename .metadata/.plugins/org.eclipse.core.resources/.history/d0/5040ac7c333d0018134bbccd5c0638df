/*
 * Display_State.h
 *
 *  Created on: 05/04/2018
 *      Author: jpone
 */

#ifndef DISPLAY_STATE_H_
#define DISPLAY_STATE_H_

typedef enum enu_displayState
{
	DISPLAY_STATE_WAINTING = 0,
	DISPLAY_STATE_TEMP,
	DISPLAY_STATE_LIGHT,

	DISPLAY_STATE_MAX
} tenu_displayState;

void Display_State_Init(void);
void Display_State_IncrementState(void);
void Display_State_Set(tenu_displayState enuNewDisplayState);
tenu_displayState Display_State_Get();

#endif /* DISPLAY_STATE_H_ */
