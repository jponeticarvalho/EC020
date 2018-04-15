/*
 * EasyWeb.h
 *
 *  Created on: 11/04/2018
 *      Author: jpone
 */

#ifndef EASYWEB_H_
#define EASYWEB_H_

#include "../Display_Ctrl/Display_State.h"

void EasyWeb_Ctrl_Init();
void EasyWeb_Ctrl_ProcessLoop();

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
