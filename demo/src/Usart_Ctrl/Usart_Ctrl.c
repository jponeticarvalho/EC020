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
#define USART_CTRL_MAX_BUFFER_SIZE			512
#define USART_CTRL_TIME_END_PACKET			TIMER_200MS

/*********************************************************
    private types.
*********************************************************/
typedef struct tag_UsartCtrl
{
	uint8_t				ucBufferRx[USART_CTRL_MAX_BUFFER_SIZE];
	uint16_t			uiSizeRx;
	uint32_t			ulReferenceTimer;
}ttag_UsartCtrl;

/*********************************************************
    private variable.
*********************************************************/
volatile ttag_UsartCtrl 			tagUsartCtrl;


/*********************************************************
    private functions prototypes.
*********************************************************/

void Usart_Ctrl_Init_Hw(void);
void cd(void);

/*********************************************************
    private functions.
*********************************************************/

void cb(void)
{
	if(tagUsartCtrl.uiSizeRx < USART_CTRL_MAX_BUFFER_SIZE)
	{
		tagUsartCtrl.ucBufferRx[tagUsartCtrl.uiSizeRx++] = (uint8_t) UART_ReceiveData(USARTx);
		tagUsartCtrl.ulReferenceTimer = Timer_getTimer();
	}
	else UART_ReceiveData(USARTx); /* Discard */
}

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

	UART_IntConfig(USARTx, UART_INTCFG_RBR, ENABLE);
	NVIC_EnableIRQ(USARTx_IRQn);

	UART_SetupCbs(USARTx, 0, &cb);

}

void UART3_IRQHandler()
{

	if(tagUsartCtrl.uiSizeRx < USART_CTRL_MAX_BUFFER_SIZE)
	{
		tagUsartCtrl.ucBufferRx[tagUsartCtrl.uiSizeRx++] = (uint8_t) UART_ReceiveData(USARTx);
		tagUsartCtrl.ulReferenceTimer = Timer_getTimer();
	}
	else UART_ReceiveData(USARTx); /* Discard */

//	UART3_StdIntHandler();

}

/*********************************************************
    public functions.
*********************************************************/

void Usart_Ctrl_Init()
{
	tagUsartCtrl.uiSizeRx = 0;
	Usart_Ctrl_Init_Hw();
}

uint16_t Usart_Ctrl_getData(uint8_t *pucData)
{
	if(!pucData)return 0;

	uint16_t uiAux = 0;

	if(tagUsartCtrl.uiSizeRx)
	{
		if(Timer_checkTimeout(tagUsartCtrl.ulReferenceTimer, USART_CTRL_TIME_END_PACKET))
		{
			memcpy(pucData, tagUsartCtrl.ucBufferRx, tagUsartCtrl.uiSizeRx);
			uiAux = tagUsartCtrl.uiSizeRx;
			tagUsartCtrl.uiSizeRx = 0;
		}
	}

	return uiAux;
}

void Usart_Ctrl_SendData(LPC_UART_TypeDef* UARTx, uint8_t *pucData, uint32_t uiDataLen)
{

	if(!pucData) return;

	uint32_t uiCounter = 0;

	UART_Send(USARTx, pucData, uiDataLen, NONE_BLOCKING);

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
