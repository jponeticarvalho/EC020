/*
 * Common.h
 *
 *  Created on: 03/04/2018
 *      Author: jpone
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "LPC17xx.h"
#include "PinDefinition.h"
#include "lpc_types.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "basic_io.h"

#define BTN_SENSORS_READ_TIME 400/portTICK_RATE_MS
#define TEMP_SENSORS_READ_TIME 500/portTICK_RATE_MS
#define LIGHT_SENSORS_READ_TIME 500/portTICK_RATE_MS

typedef enum enuSource
{
	SRC_TEMP,
	SRC_LIGHT,
	SRC_BUT,
} tenuSource;

typedef struct tagMessage
{

	tenuSource 	enuSource;
	uint32_t	ulPayload;

} ttagMessage;

typedef void (*pvCallback)(ttagMessage tagMsg);

#endif /* COMMON_H_ */
