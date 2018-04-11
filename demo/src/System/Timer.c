/*
 * Timer.c
 *
 *  Created on: 08/04/2018
 *      Author: jpone
 */

#include "Timer.h"

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
}

/*********************************************************
    public functions.
*********************************************************/

void Timer_init(void)
{
	tagTimer.uiTimerCount = 0;
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
