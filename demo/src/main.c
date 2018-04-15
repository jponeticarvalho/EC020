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
	peripheralInit(); // Habilita o Clock no GPIO
	Timer_init(); // Habilita o contador de meio milisegundos desde que o começou a execução
	Display_Ctrl_Init(); // Habilita o controle do display
	command_Init(); // Inicializa o controle de protocolo
	EasyWeb_Ctrl_Init(); // inicializa a Web

	while(1)
	{
		Display_Ctrl_ProcessLoop(); // Loop do display
		command_ProcessLoop(); //  Loop do comando do protocolo da UART
		EasyWeb_Ctrl_ProcessLoop(); // Loop da Easy Web
	}
}

void peripheralInit(void)
{

	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCGPIO, ENABLE);// FUNÇÃO DA MCU QUE HABILITA O CLOCK NA GPIO

}
