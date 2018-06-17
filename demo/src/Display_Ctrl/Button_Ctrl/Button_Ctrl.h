/*
 * Button_Ctrl.h
 *
 *  Created on: 05/04/2018
 *      Author: jpone
 */

#ifndef BUTTON_CTRL_H_
#define BUTTON_CTRL_H_

#include "lpc17xx_gpio.h"
#include "../../Common.h"
#include "../Display_State.h"

/*********************************************************
    Public Definitions.
*********************************************************/


/*********************************************************
    Public type.
*********************************************************/


/*********************************************************
    Public functions
*********************************************************/
void Button_Ctrl_Init(void);
Bool Button_Ctrl_GetValue(void);
void Button_Ctrl_setCallback(pvCallback callback);
void Button_Ctrl_Task( void *pvParameters);

#endif /* BUTTON_CTRL_H_ */
