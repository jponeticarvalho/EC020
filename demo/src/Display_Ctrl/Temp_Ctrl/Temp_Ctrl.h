/*****************************************************************************
 *   temp.h:  Header file for Temperature driver
 *
 *   Copyright(C) 2009, Embedded Artists AB
 *   All rights reserved.
 *
******************************************************************************/
#ifndef __TEMP_H
#define __TEMP_H

//#include "task.h"
#include "../../Common.h"

void Temp_Init (uint32_t (*getMsTick)(void));
int32_t Temp_Read(void);
void Temp_setCallback(pvCallback callback);
void Temp_Task( void *pvParameters);

#endif /* end __TEMP_H */
/****************************************************************************
**                            End Of File
*****************************************************************************/
