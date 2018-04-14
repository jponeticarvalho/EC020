/*****************************************************************************
 *   A demo example using several of the peripherals on the base board
 *
 *   Copyright(C) 2010, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/

#include "Usart_Ctrl/Command/Command.h"
#include "Display_Ctrl/Display_Ctrl.h"
#include "System/Timer.h"
#include "lpc17xx_clkpwr.h"
#include "EasyWeb_Ctrl/easyweb.h"

void peripheralInit(void);

int main (void)
{
	peripheralInit();
	Timer_init();
	Display_Ctrl_Init();
	command_Init();
	EasyWeb_Ctrl_Init();

	while(1)
	{
		Display_Ctrl_ProcessLoop();
		command_ProcessLoop();
		EasyWeb_Ctrl_ProcessLoop();
	}
}

void peripheralInit(void)
{

	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCGPIO, ENABLE);

}
