/*
 * Timer.c
 *
 *  Created on: 08/04/2018
 *      Author: jpone
 */

#include "Timer.h"
#include "../EasyWeb_Ctrl/tcpip.h"

/*********************************************************
    private constants.
*********************************************************/


/*********************************************************
    private types.
*********************************************************/

typedef struct tag_Timer
{
	volatile uint32_t uiTimerCount;
	volatile uint32_t uiTimerCountPar;
	volatile uint32_t uiTimerCount10ms;
	volatile uint32_t uiTimerCount10ms2;
} ttag_Timer;

/*********************************************************
    private variable.
*********************************************************/

ttag_Timer tagTimer;

/*********************************************************
    private functions prototypes.
*********************************************************/



/*********************************************************
    private functions.
*********************************************************/

void SysTick_Handler(void)
{
	tagTimer.uiTimerCount++;
	if(tagTimer.uiTimerCount%2 == 0)
		tagTimer.uiTimerCountPar++;
	if(tagTimer.uiTimerCountPar%10 == 0)
	{
		tagTimer.uiTimerCount10ms++;
		tagTimer.uiTimerCount10ms2++;
		// After 100 ticks (100 x 10ms = 1sec)
		if (tagTimer.uiTimerCount10ms >= 100) {
		  tagTimer.uiTimerCount10ms = 0;	// Reset counter
		}
		// After 20 ticks (20 x 10ms = 1/5sec)
		if (tagTimer.uiTimerCount10ms2 >= 20) {
		  tagTimer.uiTimerCount10ms2 = 0; // Reset counter
		  TCPClockHandler();  // Call TCP handler
		}
	}
}

/*********************************************************
    public functions.
*********************************************************/

void Timer_init(void)
{
	tagTimer.uiTimerCount = 0;
	tagTimer.uiTimerCountPar = 0;
	tagTimer.uiTimerCount10ms = 0;
	SysTick_Config(SystemCoreClock/2000);
	NVIC_SetPriority(SysTick_IRQn, 0);
}

void Timer_delay(tenum_Timer enuDelay)
{
	uint32_t uiStartTime;

	uiStartTime = tagTimer.uiTimerCount;
	while(Timer_checkTimeout(uiStartTime, enuDelay) == FALSE);
}

uint32_t Timer_getTimer(void)
{
	return tagTimer.uiTimerCount;
}

uint32_t Timer_getMsTimer(void)
{
	return tagTimer.uiTimerCountPar;
}

Bool Timer_checkTimeout(uint32_t uiStartTimer, tenum_Timer enuTimerReference)
{
	volatile Bool bResult = FALSE;

	if( (uint32_t)(tagTimer.uiTimerCount - uiStartTimer) >= enuTimerReference ) bResult = TRUE;
	return bResult;

}

uint32_t Timer_convertSecondsForSystemReference(uint32_t uiSeconds)
{
	return (uiSeconds * TIMER_1S);
}
