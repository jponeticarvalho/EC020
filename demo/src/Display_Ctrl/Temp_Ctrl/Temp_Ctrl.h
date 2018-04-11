/*****************************************************************************
 *   temp.h:  Header file for Temperature driver
 *
 *   Copyright(C) 2009, Embedded Artists AB
 *   All rights reserved.
 *
******************************************************************************/
#ifndef __TEMP_H
#define __TEMP_H


void Temp_Init (uint32_t (*getMsTick)(void));
int32_t Temp_Read(void);


#endif /* end __TEMP_H */
/****************************************************************************
**                            End Of File
*****************************************************************************/
