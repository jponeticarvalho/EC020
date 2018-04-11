/*
 * Usart_Ctrl.c
 *
 *  Created on: 02/04/2018
 *      Author: jpone
 */
#include "Usart_Ctrl.h"
#include "../PinDefinition.h"

/*********************************************************
    private constants.
*********************************************************/


/*********************************************************
    private types.
*********************************************************/


/*********************************************************
    private variable.
*********************************************************/

/*********************************************************
    private functions prototypes.
*********************************************************/

void Usart_Ctrl_Init_Hw(void);

/*********************************************************
    private functions.
*********************************************************/

void Usart_Ctrl_Init_Hw(void)
{

	PINSEL_CFG_Type PinCfg;
	UART_CFG_Type uartCfg;

	/* Initialize UART3 pin connect */
	PinCfg.Funcnum = PIN_DEFINITION_USART_TX_FUNC_NUM;//2;
	PinCfg.Pinnum = PIN_DEFINITION_USART_TX_PIN_NUM;//0;
	PinCfg.Portnum = PIN_DEFINITION_USART_TX_PORT_NUM;//0;
	PINSEL_ConfigPin(&PinCfg);

	PinCfg.Funcnum = PIN_DEFINITION_USART_RX_FUNC_NUM;//2;
	PinCfg.Pinnum = PIN_DEFINITION_USART_RX_PIN_NUM;//0;
	PinCfg.Portnum = PIN_DEFINITION_USART_RX_PORT_NUM;//0;
	PINSEL_ConfigPin(&PinCfg);

	uartCfg.Baud_rate 	= USART_CTRL_BAUDRATE;
	uartCfg.Databits	= USART_CTRL_DATA_BITS;
	uartCfg.Parity 		= USART_CTRL_PARITY;
	uartCfg.Stopbits 	= USART_CTRL_STOP_BITS;

	UART_Init(USARTx, &uartCfg);
	UART_TxCmd(USARTx, ENABLE);

}

/*********************************************************
    public functions.
*********************************************************/

void Usart_Ctrl_Init()
{
	Usart_Ctrl_Init_Hw();
}

void Usart_Ctrl_SendData(LPC_UART_TypeDef* UARTx, uint8_t *pucData, uint32_t uiDataLen)
{

	if(!pucData) return;

	uint32_t uiCounter = 0;

	while( uiCounter < uiDataLen )
	{
		UART_SendData(UARTx, pucData[uiCounter++]);
	}

}

void Usart_Ctrl_ReceiveData(LPC_UART_TypeDef* UARTx, uint8_t *pucData, uint32_t uiDataLen)
{

	if(!pucData) return;

	uint32_t uiCounter = 0;

	while( uiCounter < uiDataLen )
	{
		pucData[++uiCounter] = UART_ReceiveData(UARTx);
	}

}

void Usart_Ctrl_ReceiveLine(LPC_UART_TypeDef* UARTx, uint8_t *pucData)
{

	if(!pucData) return;

	uint32_t uiCounter = 0;

	pucData[uiCounter] = UART_ReceiveData(UARTx);

	while( pucData[uiCounter] != '\n' && pucData[uiCounter] != '\r' )
	{

		pucData[++uiCounter] = UART_ReceiveData(UARTx);

	}

}
