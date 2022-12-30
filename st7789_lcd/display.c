// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 5/6/2022 by behm
// ******************************************************

#include "display.h"
#include "qtc.h"
#include <propeller.h>
#include <cog.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "project_io.h"
#include "propfont.h"
#include "BKlogo.h"
#include "eefs.h"

uint32_t dispMask = 0xffff;
uint32_t csmask = 0;
_Bool disp1 = false;

const int width = 320;
const int height = 240;

color_t fg, bg;

//static void (*transform)(int &x, int &y);

static const uint16_t initSeq0[] =
{
	0x03, 0x0000, 0x0c, 0x0000, 0xa4, 0x0001, 0
};
static const uint16_t initSeq1[] =
{
	0x60, 0xa700, 0x08, 0x0503,
	0x30, 0x0500, 0x31, 0x3711, 0x32, 0x0605, 0x33, 0x120d, 0x34, 0x1202,
	0x35, 0x0d0a, 0x36, 0x3506, 0x37, 0x1107, 0x38, 0x0005, 0x39, 0x0212,
	0x90, 0x001d, 0x10, 0x0310, 0x11, 0x0232, 0x13, 0x1400, 0x12, 0x01bc,
	0
};
static const uint16_t initSeq2[] =
{
	0x01, 0x0500, 0x02, 0x0200, 0x03, 0x40b8, 0x09, 0x0001,
	0x0a, 0x0008, 0x0c, 0x0000, 0x0d, 0x0000, 0x0e, 0x0030, 0x0f, 0x0000,
	0x50, 0x0000, 0x51, 0x00ef, 0x52, 0x0000, 0x53, 0x013f, 0x61, 0x0000,
	0x6a, 0x0000, 0x80, 0x0000, 0x81, 0x0000, 0x82, 0x0000,
	0x91, 0x0003, 0x92, 0x0100, 0x93, 0x0201, 0x94, 0x0001,
	0xc0, 0x0000, 0xf3, 0x0020, 0x20, 0x0000, 0x21, 0x0000,
	0
};
static const uint16_t initSeq3[] =
{
	/*0x03, 0x40b8,*/ 0x20, 0x0000, 0x21, 0x0000, 0
};

static void chkio()
{
	uint32_t o = outa;
	uint32_t i = ina;
	uint32_t d = (o ^ i) & 	(0xffff | (1 << p_dres) | (1 << p_cs0) | (1 << p_cs1) | (1 << p_a0) | (1 << p_wr));
	if (d)
	{
		printf("delta=%08lx %08lx %08lx\n", d, i, o);
	}

}

static void transform(int &x, int &y, const int w, const int h)
{
	if (disp1)
	{
		y = height - y - h;
	}
	else
	{
		x = width - x - w;
	}
}

static void outData(uint16_t d)
{
	outa = (outa & ~0xffff) | d;
}

static void wrPulse()
{
	_pinl(p_wr);
//	_waitus(5);
//	chkio();
	_pinh(p_wr);
//	chkio();
}

void selDisplay(int n)
{
	switch (n)
	{
	case 0:
		csmask = 1 << p_cs0;
		disp1 = false;
		break;
	case 1:
		csmask = 1 << p_cs1;
		disp1 = true;
		break;
	default:
		csmask = (1 << p_cs0) | (1 << p_cs1);
		disp1 = false;
		break;
	}
}

static void writeReg(uint16_t r, uint16_t d)
{
	outa &= ~csmask;
	outData(r);
	_pinl(p_a0);
	wrPulse();
	_pinh(p_a0);
	outData(d);
	wrPulse();
	outa |=  (1 << p_cs0) | (1 << p_cs1);
//	printf("writereg(%02x)-%04x\n", r, d);
}

static void writeSeq(const uint16_t *s)
{
	while(*s)
	{
		const uint16_t r = *s++;
		writeReg(r, *s++);
	}
}

void enableDisplay()
{
	writeReg(0x07, 0x0100);
}

void initDisplay()
{
	selDisplay(3);
	dispMask = 0xffff | (1 << p_dres) | (1 << p_cs0) | (1 << p_cs1) | (1 << p_a0) | (1 << p_wr);
	outa |= dispMask;
	dira |= dispMask;

	_pinl(p_dres);
	_waitms(10);
	_pinh(p_dres);
	_waitms(10);
	_pinl(p_cs0);
	_pinl(p_cs1);
	outData(0);
	_pinl(p_a0);
	wrPulse();
	wrPulse();
	wrPulse();
	_pinh(p_a0);
	_pinh(p_cs0);
	_pinh(p_cs1);
	writeReg(0xa4, 0x0001);
	_waitms(1);
//	printf("calib\n");
	writeSeq(initSeq1);
//	printf("initSeq1\n");
	_waitms(100);
	writeSeq(initSeq2);
//	printf("initSeq2\n");
	enableDisplay();
//	printf("enableDisplay\n");
	fg = 0xffff;
	bg = 0;
	fillScreen(bg);
}

void setBg(color_t b)
{
	bg = b;
}

void setFg(color_t f)
{
	fg = f;
}

void setRect(int x, int y, int w, int h)
{
	transform(x, y, w, h);
	int xe = x + w - 1;
	int ye = y + h - 1;
	writeReg(0x50, y);
	writeReg(0x51, ye);
	writeReg(0x52, x);
	writeReg(0x53, xe);
	writeReg(0x20, y);	// set cursor
	writeReg(0x21, x);
}

void fillScreen(color_t color)
{
	fillRect(0, 0, width, height, color);
}

void fillRect(int x, int y, int w, int h, color_t color)
{
//	printf("fillr(%d,%d,%d,%d,%04x)\n", x, y, w, h, color);
	setRect(x, y, w, h);
	outa &= ~csmask;
	outData(0x22);
	_pinl(p_a0);
	wrPulse();
	_pinh(p_a0);
	outData(color);
	for (int i = 0; i < w * h; ++i)
	{
		wrPulse();
	}
	outa |= csmask;
}

static const color_t rainbowcolors[] =
{
	0xffff, 0x0000, 0x001f, 0x03ff,
	0x07ff, 0x07e0, 0x7fe0, 0xefe0,
	0xfbe0, 0xf800, 0xf80f, 0xf81f,
	0x7c1f, 0x001f
};

void rainbow()
{
	selDisplay(3);
	const int n = sizeof(rainbowcolors) / sizeof(rainbowcolors[0]);
	uint16_t w = width / n;
	int d = (width - (w * n)) / 2;
	for (int i = 0; i < n; ++i)
	{
		selDisplay(0);
		fillRect(d + i * w, 0, w, height, rainbowcolors[i]);
		selDisplay(1);
		fillRect(d + i * w, 0, w, height, rainbowcolors[i]);
	}
	selDisplay(0);
	drawString(0, 0, "0123456789");
	setBg(rgb565(0, 0, 255));
	setFg(rgb565(255, 255, 0));
	selDisplay(1);
	drawString(40, 30, "Hello World!");
}

int drawChar(int x, int y, char c)
{
	setRect(x, y, propfont.w, propfont.h);
//	printf("drawc(%d,%d,'%c') %d.%d\n", x, y, c, propfont.w, propfont.h);
	const uint8_t *p = getFont(c);
	int delta = 2;
	if (disp1)
	{
		p += (propfont.bc-2);
		delta = -2;
	}
	outa &= ~csmask;
	outData(0x22);
	_pinl(p_a0);
	wrPulse();
	_pinh(p_a0);
	uint16_t bc = p[0] | (p[1] << 8);
	uint16_t mask = disp1 ? 0x0001 : 0x8000;
	const int pixc = propfont.w * propfont.h;
	for (int i = 0; i < pixc; ++i)
	{

		if (bc & mask)
		{
			outData(fg);
		}
		else
		{
			outData(bg);
		}
		wrPulse();
		if (disp1)
		{
			mask = (mask << 1) & 0xffff;
		}
		else
		{
			mask >>= 1;
		}
		if (mask == 0)
		{
			mask= disp1 ? 0x0001 : 0x8000;
			p += delta;
			bc = p[0] | (p[1] << 8);
		}
	}
	outa |= csmask;
	return x + propfont.w;
}

void drawString(int x, int y, const char *s)
{
	while (*s)
	{
		x = drawChar(x, y, *s++);
	}
}

void drawHLine(int x, int y, int w, color_t color)
{
	fillRect(x, y, w, 1, color);
}

void drawVLine(int x, int y, int h, color_t color)
{
	fillRect(x, y, 1, h, color);
}

void show()
{
	fillScreen(0);
	static const color_t cc[8] =
	{
		rgb565(0, 0, 0), rgb565(0, 0, 255), rgb565(0, 255, 0), rgb565(0, 255, 255),
		rgb565(255, 0, 0), rgb565(255, 0, 255), rgb565(255, 255, 0), rgb565(255, 255, 255)
	};
	for (int i = 0; i < 8; ++i)
	{
		fillRect(30+i*30, 5, 30, 30, cc[i]);
		drawRect(30+i*30, 5, 30, 30, rgb565(255, 255, 255));
	}
#if 0
	for (int i = 0; i  < width; i += 10)
	{
		_waitms(10);
		drawVLine(i, 0, height, rgb565(255, 0, 0));
	}
	for (int i = 0; i  < height; i += 10)
	{
		_waitms(10);
		drawHLine(0, i, width, rgb565(0, 255, 0));
	}
#endif
	drawRect(0, 0, width, height, rgb565(0, 0, 255));
	drawRect(95, 95, 50, 50, rgb565(255, 0, 255));
	fillRect(155, 105, 50, 50, rgb565(255, 0, 255));
	for (int i = 0; i < 7; ++i)
	{
		int ii = i  * 20;
		drawRect(ii, ii, 320-2*ii, 240-2*ii, -1);
		drawChar(ii, ii, i+'0');
	}
	drawString(0, 240-32, "Hello World!");
}

void drawRect(int x, int y, int w, int h, color_t color)
{
	drawHLine(x, y, w, color);
	drawHLine(x, y+h-1, w, color);
	drawVLine(x, y, h, color);
	drawVLine(x+w-1, y, h, color);
}

void drawLogo(int x, int y)
{
	Logo head;
	int fn = getBkLogoHead(&head);
	const bpl = head.w /** head.bitPix*/ / 8;
//	printf("drawLogo %d w=%d h=%d bpl=%d\n", fn, head.w, head.h, bpl);
	if (fn < 0)
	{
		return;
	}
//	drawRect(x-1, y-1, head.w+2, head.h+2, 0);
	setRect(x, y, head.w, head.h);
	outa &= ~csmask;
	outData(0x22);
	_pinl(p_a0);
	wrPulse();
	_pinh(p_a0);
	uint8_t imask = disp1 ? 0x80 : 0x01;
	for (int iy = 0; iy < head.h; ++iy)
	{
		uint16_t off = sizeof(head) + (iy+1) * bpl;
		if (disp1)
		{
			off = sizeof(head) + (head.h-iy-1) * bpl-1;
		}
		uint8_t mask = 0x00;
		uint8_t pix;
//		printf("dl y=%d %02x ", iy, pix);
		for (int ix = 0; ix < head.w; ++ix)
		{
			if (disp1)
			{
				mask >>= 1;
			}
			else
			{
				mask <<= 1;
			}
			if (mask == 0)
			{
				mask = imask;
				if (disp1)
				{
					++off;
				}
				else
				{
					--off;
				}
				eefs_read(fn, off, &pix, 1);
//				printf("dl y=%d,x=%d %02x ", iy, ix, pix);
			}
			if (pix & mask)
			{
				outData(head.colors[1]);
			}
			else
			{
				outData(head.colors[0]);
			}
			wrPulse();
		}
	}
}
