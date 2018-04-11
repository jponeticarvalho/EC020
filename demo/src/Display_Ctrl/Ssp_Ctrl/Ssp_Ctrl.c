/*
 * Ssp_Ctrl.c
 *
 *  Created on: 04/04/2018
 *      Author: jpone
 */

#include "Ssp_Ctrl.h"
#include "../../PinDefinition.h"

void Ssp_Ctrl_Init_Hw(void)
{
	SSP_CFG_Type SSP_ConfigStruct;
	PINSEL_CFG_Type PinCfg;

	/*
	 * Initialize SPI pin connect
	 * P0.7 - SCK;
	 * P0.8 - MISO
	 * P0.9 - MOSI
	 * P2.2 - SSEL - used as GPIO
	 */
	PinCfg.Funcnum = PIN_DEFINITION_SSP_SCK_FUNC_NUM;
	PinCfg.OpenDrain = PIN_DEFINITION_SSP_SCK_OPEN_DRAIN;
	PinCfg.Pinmode = PIN_DEFINITION_SSP_SCK_PIN_MODE;
	PinCfg.Pinnum = PIN_DEFINITION_SSP_SCK_PIN_NUM;
	PinCfg.Portnum = PIN_DEFINITION_SSP_SCK_PORT_NUM;
	PINSEL_ConfigPin(&PinCfg);

	PinCfg.Funcnum = PIN_DEFINITION_SSP_MISO_FUNC_NUM;
	PinCfg.OpenDrain = PIN_DEFINITION_SSP_MISO_OPEN_DRAIN;
	PinCfg.Pinmode = PIN_DEFINITION_SSP_MISO_PIN_MODE;
	PinCfg.Pinnum = PIN_DEFINITION_SSP_MISO_PIN_NUM;
	PinCfg.Portnum = PIN_DEFINITION_SSP_MISO_PORT_NUM;
	PINSEL_ConfigPin(&PinCfg);

	PinCfg.Funcnum = PIN_DEFINITION_SSP_MOSI_FUNC_NUM;
	PinCfg.OpenDrain = PIN_DEFINITION_SSP_MOSI_OPEN_DRAIN;
	PinCfg.Pinmode = PIN_DEFINITION_SSP_MOSI_PIN_MODE;
	PinCfg.Pinnum = PIN_DEFINITION_SSP_MOSI_PIN_NUM;
	PinCfg.Portnum = PIN_DEFINITION_SSP_MOSI_PORT_NUM;
	PINSEL_ConfigPin(&PinCfg);

	PinCfg.Funcnum = PIN_DEFINITION_SSP_SSEL_FUNC_NUM;
	PinCfg.OpenDrain = PIN_DEFINITION_SSP_SSEL_OPEN_DRAIN;
	PinCfg.Pinmode = PIN_DEFINITION_SSP_SSEL_PIN_MODE;
	PinCfg.Pinnum = PIN_DEFINITION_SSP_SSEL_PIN_NUM;
	PinCfg.Portnum = PIN_DEFINITION_SSP_SSEL_PORT_NUM;
	PINSEL_ConfigPin(&PinCfg);

	SSP_ConfigStructInit(&SSP_ConfigStruct);

	// Initialize SSP peripheral with parameter given in structure above
	SSP_Init(SSPx, &SSP_ConfigStruct);

	// Enable SSP peripheral
	SSP_Cmd(SSPx, ENABLE);
}

void Ssp_Ctrl_Init(void)
{
	Ssp_Ctrl_Init_Hw();
}

void Ssp_Ctrl_Write(uint8_t *pcTxData, uint8_t *pcRxData, uint32_t uiLenght)
{

    SSP_DATA_SETUP_Type xferConfig;

	xferConfig.tx_data = pcTxData;
	xferConfig.rx_data = pcRxData;
	xferConfig.length  = uiLenght;

    SSP_ReadWrite(SSPx, &xferConfig, SSP_TRANSFER_POLLING);

}
