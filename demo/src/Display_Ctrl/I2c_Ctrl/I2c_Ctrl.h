/*
 * I2c_Ctrl.h
 *
 *  Created on: 03/04/2018
 *      Author: jpone
 */
#include "lpc17xx_i2c.h"
#include "lpc17xx_pinsel.h"

#ifndef I2C_CTRL_H_
#define I2C_CTRL_H_

#define I2Cx LPC_I2C2
#define CLOCK_RATE 100000

void	I2c_Ctrl_Init(void);
int		I2c_Ctrl_Read(uint8_t ucAddr, uint8_t* pucData, uint32_t uiDataLen);
int		I2c_Ctrl_Write(uint8_t ucAddr, uint8_t* pucData, uint32_t uiDataLen);

#endif /* I2C_CTRL_H_ */
