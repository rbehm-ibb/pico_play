// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/28/2022 by behm
// ******************************************************

#ifndef ST7789_H
#define ST7789_H

#include <iostream>
#include "hardware/pio.h"
#include "point.h"
#include "ibfont.h"

typedef uint16_t color_t;
#define rgb565(r, g, b) (((b & 0x1f) << 0) | ((g & 0x3f) << 5) | ((r & 0x1f) << 11))

class St7789
{
public:
	St7789();
	void clear(uint16_t color = 0);
	void fillRect(const Rect &r, uint16_t color = 0);
	void startPixels();
	void put(uint8_t d);
	void put(uint16_t d) { put(static_cast<uint8_t>(d >> 8)); put(static_cast<uint8_t>(d & 0xff)); }
	void put(int d) { put(static_cast<uint16_t>(d)); }
	void put(uint8_t *d, size_t count);
	void put(uint16_t *d, size_t count);
	void setBl(bool on);
	Rect screen() const { return m_win; }
	void setFullScreen() { setWindow(m_screenWin); }
	void drawHLine(const Point &p, uint w, color_t color);
	void drawVLine(const Point &p, uint w, color_t color);
	void drawRect(const Rect &r, color_t color);
	void drawChar(const Point &p, char c);
	void drawChar(char c);
	void drawString(const char *s);
	void rainbow();
	void setFont(const IbFont *newFont) { m_font = newFont; }
	color_t fg() const { return m_fg; }
	void setFg(color_t newFg) { m_fg = newFg; }
	color_t bg() const { return m_bg; }
	void setBg(color_t newBg) { m_bg = newBg; }

	Point cursor() const { return m_cursor; }
	void setCursor(Point newCursor) { m_cursor = newCursor; }

private:
	const PIO pio;
	static constexpr uint sm = 0;
	const Rect m_screenWin;
	Rect m_win;
	Point m_cursor;
	const IbFont *m_font;
	color_t m_fg;
	color_t m_bg;
	void setDcCs(bool dc, bool cs);
	void init();
	void writeCmd(const uint8_t *cmd, size_t count);
	void writeCmd(const uint8_t cmd);
	void setWindow(const Point s, const Point e) { setWindow(Rect(s, e)); }
	void setWindow(const Rect &r);
};

#endif // ST7789_H
