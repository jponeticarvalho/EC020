/*
 * Light_Ctrl.h
 *
 *  Created on: 03/04/2018
 *      Author: jpone
 */

#ifndef LIGHT_CTRL_H_
#define LIGHT_CTRL_H_

#include "../I2c_Ctrl/I2c_Ctrl.h"

typedef enum
{
    LIGHT_MODE_D1,
    LIGHT_MODE_D2,
    LIGHT_MODE_D1D2
} light_mode_t;

typedef enum
{
    LIGHT_WIDTH_16BITS,
    LIGHT_WIDTH_12BITS,
    LIGHT_WIDTH_08BITS,
    LIGHT_WIDTH_04BITS
} light_width_t;

typedef enum
{
    LIGHT_RANGE_1000,
    LIGHT_RANGE_4000,
    LIGHT_RANGE_16000,
    LIGHT_RANGE_64000
} light_range_t;

typedef enum
{
    LIGHT_CYCLE_1,
    LIGHT_CYCLE_4,
    LIGHT_CYCLE_8,
    LIGHT_CYCLE_16
} light_cycle_t;


void 		Light_Ctrl_Init (void);
void 		Light_Ctrl_Enable (void);
uint32_t 	Light_Ctrl_Read(void);
void 		Light_Ctrl_SetMode(light_mode_t mode);
void 		Light_Ctrl_SetWidth(light_width_t width);
void 		Light_Ctrl_SetRange(light_range_t newRange);
void 		Light_Ctrl_SetHiThreshold(uint32_t luxTh);
void 		Light_Ctrl_SetLoThreshold(uint32_t luxTh);
void 		Light_Ctrl_SetIrqInCycles(light_cycle_t cycles);
uint8_t 	Light_Ctrl_GetIrqStatus(void);
void 		Light_Ctrl_ClearIrqStatus(void);
void 		Light_Ctrl_Shutdown(void);

#endif /* LIGHT_CTRL_H_ */
