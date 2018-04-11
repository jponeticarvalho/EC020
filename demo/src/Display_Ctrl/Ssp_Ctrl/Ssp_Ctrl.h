/*
 * Ssp_Ctrl.h
 *
 *  Created on: 04/04/2018
 *      Author: jpone
 */

#ifndef SSP_CTRL_H_
#define SSP_CTRL_H_

#include "lpc17xx_ssp.h"
#include "lpc17xx_pinsel.h"

#define SSPx LPC_SSP1

void Ssp_Ctrl_Init(void);
void Ssp_Ctrl_Write(uint8_t *pcTxData, uint8_t *pcRxData, uint32_t uiLenght);

#endif /* SSP_CTRL_H_ */
