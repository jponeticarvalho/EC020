/*
 * Oled_Ctrl.h
 *
 *  Created on: 03/04/2018
 *      Author: jpone
 */

#ifndef OLED_CTRL_H_
#define OLED_CTRL_H_

#define OLED_DISPLAY_WIDTH  96
#define OLED_DISPLAY_HEIGHT 64

#define SCREENSTRING_MAXLEN 16

#include <string.h>
#include "lpc17xx_gpio.h"
#include "Fonte5x7.h"
#include "../Ssp_Ctrl/Ssp_Ctrl.h"

typedef enum
{
    OLED_COLOR_BLACK,
    OLED_COLOR_WHITE
} oled_color_t;

typedef struct tag_screenStrings
{
	uint8_t screenString_Line1[SCREENSTRING_MAXLEN];
	uint8_t screenString_Line2[SCREENSTRING_MAXLEN];
	uint8_t screenString_Line3[SCREENSTRING_MAXLEN];
	uint8_t screenString_Line4[SCREENSTRING_MAXLEN];
	uint8_t screenString_Line5[SCREENSTRING_MAXLEN];
	uint8_t screenString_Line6[SCREENSTRING_MAXLEN];
	uint8_t screenString_Line7[SCREENSTRING_MAXLEN];
} ttag_screenStrings;

void Oled_Ctrl_Init (void);
void Oled_Ctrl_PutPixel(uint8_t x, uint8_t y, oled_color_t color);
void Oled_Ctrl_Line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, oled_color_t color);
void Oled_Ctrl_Circle(uint8_t x0, uint8_t y0, uint8_t r, oled_color_t color);
void Oled_Ctrl_Rect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, oled_color_t color);
void Oled_Ctrl_FillRect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, oled_color_t color);
void Oled_Ctrl_ClearScreen(oled_color_t color);
void Oled_Ctrl_PutString(uint8_t x, uint8_t y, uint8_t *pStr, oled_color_t fb,
        oled_color_t bg);
uint8_t Oled_Ctrl_PutChar(uint8_t x, uint8_t y, uint8_t ch, oled_color_t fb, oled_color_t bg);
void Oled_Ctrl_PutScreen(ttag_screenStrings tagScreenStrings, oled_color_t tagFontColor,
		oled_color_t tagBrackgroungColor);

#endif /* OLED_CTRL_H_ */
