/*
 * I2c_Ctrl.c
 *
 *  Created on: 03/04/2018
 *      Author: jpone
 */

#include "I2c_Ctrl.h"
#include "../../PinDefinition.h"

void I2c_Ctrl_Init_Hw(void)
{
	PINSEL_CFG_Type PinCfg;

	/* Initialize I2C2 pin connect */
	PinCfg.Funcnum = PIN_DEFINITION_I2C_SDA_FUNC_NUM;
	PinCfg.Pinnum = PIN_DEFINITION_I2C_SDA_PIN_NUM;
	PinCfg.Portnum = PIN_DEFINITION_I2C_SDA_PORT_NUM;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Funcnum = PIN_DEFINITION_I2C_SCL_FUNC_NUM;
	PinCfg.Pinnum = PIN_DEFINITION_I2C_SCL_PIN_NUM;
	PinCfg.Portnum = PIN_DEFINITION_I2C_SCL_PORT_NUM;
	PINSEL_ConfigPin(&PinCfg);

	// Initialize I2C peripheral
	I2C_Init(I2Cx, CLOCK_RATE);

	/* Enable I2C1 operation */
	I2C_Cmd(I2Cx, ENABLE);
}

void I2c_Ctrl_Init(void)
{
	I2c_Ctrl_Init_Hw();
}

int I2c_Ctrl_Read(uint8_t ucAddr, uint8_t* pucData, uint32_t uiDataLen)
{
	I2C_M_SETUP_Type rxsetup;

	rxsetup.sl_addr7bit = ucAddr;
	rxsetup.tx_data = NULL;	// Get address to read at writing address
	rxsetup.tx_length = 0;
	rxsetup.rx_data = pucData;
	rxsetup.rx_length = uiDataLen;
	rxsetup.retransmissions_max = 3;

	if (I2C_MasterTransferData(I2Cx, &rxsetup, I2C_TRANSFER_POLLING) == SUCCESS){
		return (0);
	} else {
		return (-1);
	}
}

int I2c_Ctrl_Write(uint8_t ucAddr, uint8_t* pucData, uint32_t uiDataLen)
{
	I2C_M_SETUP_Type txsetup;

	txsetup.sl_addr7bit = ucAddr;
	txsetup.tx_data = pucData;
	txsetup.tx_length = uiDataLen;
	txsetup.rx_data = NULL;
	txsetup.rx_length = 0;
	txsetup.retransmissions_max = 3;

	if (I2C_MasterTransferData(I2Cx, &txsetup, I2C_TRANSFER_POLLING) == SUCCESS){
		return (0);
	} else {
		return (-1);
	}
}
