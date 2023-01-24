// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 5/6/2022 by behm
// ******************************************************

#ifndef DISPLAY_H
#define DISPLAY_H

#include "qtc.h"
#include <stdint.h>

#define rgb565(r, g, b) (((r & 0x1f) << 0) | ((g & 0x3f) << 5) | ((b & 0x1f) << 11))
typedef struct S_Font
{
	uint16_t pixc;
	uint8_t w, h, bpc;
	char first;
	uint8_t font[];
} Font;
typedef uint16_t color_t;

void initDisplay()  __fromfile("display.c");
void selDisplay(int n) __fromfile("display.c");
void setRect(int x, int y, int w, int h) __fromfile("display.c");
void fillScreen(color_t color) __fromfile("display.c");
void fillRect(int x, int y, int w, int h, uint16_t color) __fromfile("display.c");
void setBg(color_t b) __fromfile("display.c");
void setFg(color_t f) __fromfile("display.c");
void drawHLine(int x, int y, int w, color_t color) __fromfile("display.c");
void drawVLine(int x, int y, int h, color_t color) __fromfile("display.c");
void drawRect(int x, int y, int w, int h, color_t color) __fromfile("display.c");
int drawChar(int x, int y, char c) __fromfile("display.c");
void drawString(int x, int y, const char *s) __fromfile("display.c");
void drawLogo(int x, int y) __fromfile("display.c");
void rainbow();
void show();


struct __using("display.c") Display;

#endif // DISPLAY_H
