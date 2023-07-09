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

enum SpiPins { DC=16, CS=13, Clk=14, Mosi=15, /*Miso=15, */ Res=17, BL=18 };

typedef uint16_t color_t;
#define rgb565(r, g, b) (((b & 0x1f) << 0) | ((g & 0x3f) << 5) | ((r & 0x1f) << 11))

class St7789
{
public:
	enum Colors : color_t
	{
		BLACK = 0x0000,
		NAVY = 0x000F,
		DARKGREEN = 0x03E0,
		DARKCYAN = 0x03EF,
		MAROON = 0x7800,
		PURPLE = 0x780F,
		OLIVE = 0x7BE0,
		LIGHTGREY = 0xC618,
		DARKGREY = 0x7BEF,
		BLUE = 0x001F,
		GREEN = 0x07E0,
		CYAN = 0x07FF,
		RED = 0xF800,
		MAGENTA = 0xF81F,
		YELLOW = 0xFFE0,
		WHITE = 0xFFFF,
		ORANGE = 0xFD20,
		GREENYELLOW = 0xAFE5,
		PINK = 0xFC18
	};
	St7789();
	void clear(uint16_t color = 0);
	void fillRect(const Rect &r, uint16_t color = 0);
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
	void setCursor(int x, int y) { m_cursor = Point(x, y); }
	Size charSize() const;
	Size charSize(const char *s) const;
	Rect win() const { return m_win; }

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
	void startPixels();
	void put(uint8_t d);
	void put(uint16_t d) { put(static_cast<uint8_t>(d >> 8)); put(static_cast<uint8_t>(d & 0xff)); }
	void put(int d) { put(static_cast<uint16_t>(d)); }
	void put(uint8_t *d, size_t count);
	void put(uint16_t *d, size_t count);
	void init();
	void writeCmd(const uint8_t *cmd, size_t count);
	void writeCmd(const uint8_t cmd);
	void setWindow(const Point s, const Point e) { setWindow(Rect(s, e)); }
	void setWindow(const Rect &r);
};

#endif // ST7789_H
