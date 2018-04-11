/*
 * Timer.h
 *
 *  Created on: 08/04/2018
 *      Author: jpone
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "../Common.h"

typedef enum enum_Timer
{

	TIMER_NULL = 0,
	TIMER_50US = 1,
	TIMER_100US = 2,
	TIMER_200US = 4,
	TIMER_700US = 14,

	TIMER_1MS = 20,
	TIMER_5MS = 100,
	TIMER_5_5MS = 110,
	TIMER_6MS = 120,

	TIMER_10MS = 200,
	TIMER_15MS = 300,

	TIMER_30MS = 600,
	TIMER_50MS = 1000,
	TIMER_70MS = 1400,

	TIMER_200MS = 4000,
	TIMER_500MS = 10000,

	TIMER_1S = 20000,
	TIMER_3S = 60000,
	TIMER_5S = 100000,

	TIMER_10S = 200000,
	TIMER_30S = 600000,

} tenum_Timer;

void Timer_init(void);
void Timer_delay(tenum_Timer enuDelay);
uint32_t Timer_getTimer(void);
uint32_t Timer_getMsTimer(void);
Bool Timer_checkTimeout(uint32_t uiStartTimer, tenum_Timer enuTimerReference);
uint32_t Timer_convertSecondsForSystemReference(uint32_t uiSeconds);

#endif /* TIMER_H_ */
