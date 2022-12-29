// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/28/2022 by behm
// ******************************************************

#ifndef ST7789_H
#define ST7789_H

#include <iostream>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "point.h"

typedef uint16_t color_t;
#define rgb565(r, g, b) (((r & 0x1f) << 0) | ((g & 0x3f) << 5) | ((b & 0x1f) << 11))

class St7789
{
public:
	St7789();
	void clear(uint16_t color = 0);
	void fillRect(const Rect &r, uint16_t color = 0);
	void startPixels();
	void put(uint8_t d);
	void put(uint16_t d) { put(static_cast<uint8_t>(d >> 8)); put(static_cast<uint8_t>(d & 0xff)); }
	void put(uint8_t *d, size_t count);
	void put(uint16_t *d, size_t count);
	void setBl(bool on);
	Rect screen() const { return m_win; }
	void setFullScreen() { setWindow(m_screenWin); }
	void drawHLine(uint x, uint y, uint w, color_t color);

	void rainbow();
private:
	const PIO pio;
	static constexpr uint sm = 0;
	const Rect m_screenWin;
	Rect m_win;
	void setDcCs(bool dc, bool cs);
	void init();
	void writeCmd(const uint8_t *cmd, size_t count);
	void writeCmd(const uint8_t cmd);
//	void setWindow(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye) { setWindow(Point(xs, ys), Point(xe, ye)); }
	void setWindow(const Point s, const Point e);
	void setWindow(const Rect &r);
};

#endif // ST7789_H
