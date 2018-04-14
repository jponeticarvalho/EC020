/*
 * Command.h
 *
 *  Created on: 03/04/2018
 *      Author: jpone
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include "../../Common.h"
#include "../../Display_Ctrl/Display_State.h"
#include "../Usart_Ctrl.h"

void command_Init(void);
void command_ProcessLoop(void);

#endif /* COMMAND_H_ */
