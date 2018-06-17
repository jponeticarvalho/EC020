/*
 * EasyWeb.h
 *
 *  Created on: 11/04/2018
 *      Author: jpone
 */

#ifndef EASYWEB_H_
#define EASYWEB_H_

#include "../Display_Ctrl/Display_State.h"
#include "../Display_Ctrl/Temp_Ctrl/Temp_Ctrl.h"
#include "../Display_Ctrl/Light_Ctrl/Light_Ctrl.h"
#include "tcpip.h"
#include "../Common.h"

xQueueHandle Http_server_queue;

void EasyWeb_Ctrl_Init();
void EasyWeb_Ctrl_ProcessLoop();
void EasyWeb_Ctrl_UpdaterTask();

void start(void);
void InitOsc(void);                              // prototypes
void InitPorts(void);
void HTTPServer(void);
void InsertDynamicValues(void);
unsigned int GetAD7Val(void);
unsigned int GetTempVal(void);

unsigned char *PWebSide;                         // pointer to webside
unsigned int HTTPBytesToSend;                    // bytes left to send

unsigned char HTTPStatus;                        // status byte
#define HTTP_SEND_PAGE               0x01        // help flag

#endif /* EASYWEB_H_ */
