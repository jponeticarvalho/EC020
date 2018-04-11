/*
 * Display_Ctrl.h
 *
 *  Created on: 03/04/2018
 *      Author: jpone
 */

#ifndef DISPLAY_CTRL_H_
#define DISPLAY_CTRL_H_

#include "I2c_Ctrl/I2c_Ctrl.h"
#include "Light_Ctrl/Light_Ctrl.h"
#include "Oled_Ctrl/Oled_Ctrl.h"
#include "Temp_Ctrl/Temp_Ctrl.h"
#include "Ssp_Ctrl/Ssp_Ctrl.h"
#include "Button_Ctrl/Button_Ctrl.h"
#include "Display_State.h"
#include "../System/Timer.h"

void Display_Ctrl_Init(void);
void Display_Ctrl_ProcessLoop();

#endif /* DISPLAY_CTRL_H_ */
