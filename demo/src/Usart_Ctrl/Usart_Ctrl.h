/*
 * Usart_Ctrl.h
 *
 *  Created on: 02/04/2018
 *      Author: jpone
 */

#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"
#include "../System/Timer.h"

#ifndef USART_CTRL_H_
#define USART_CTRL_H_

#define USARTx					LPC_UART3
#define USARTx_IRQn				UART3_IRQn

#define USART_CTRL_BAUDRATE		115200
#define USART_CTRL_DATA_BITS	UART_DATABIT_8
#define USART_CTRL_PARITY		UART_PARITY_NONE
#define USART_CTRL_STOP_BITS	UART_STOPBIT_1

void Usart_Ctrl_Init();
void Usart_Ctrl_SendData(LPC_UART_TypeDef* UARTx, uint8_t *pucData, uint32_t uiDataLen);
void Usart_Ctrl_ReceiveData(LPC_UART_TypeDef* UARTx, uint8_t *pucData, uint32_t uiDataLen);
void Usart_Ctrl_ReceiveLine(LPC_UART_TypeDef* UARTx, uint8_t *pucData);

#endif /* USART_CTRL_H_ */
