// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/28/2022 by behm
// ******************************************************

#include "st7789.h"
#include <iostream>
#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/pio.h>
#include <hardware/gpio.h>
#include <hardware/pwm.h>
//#include "ibblib/debug.h"
#include "st7789_lcd.pio.h"
#include "propfont.h"

using namespace std;

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

//#define PIN_DIN 0
//#define PIN_CLK 1
//#define PIN_CS 2
//#define PIN_DC 3
//#define PIN_RESET 4
//#define PIN_BL 5

#define SERIAL_CLK_DIV 1.f

//static_assert(SCREEN_WIDTH < 256, "SCREEN_WIDTH must be 8bit");
//static_assert(SCREEN_HEIGHT < 256, "SCREEN_HEIGHT must be 8bit");

St7789::St7789()
	: pio(pio0)
	, m_screenWin(Point(0, 0), Size(SCREEN_WIDTH, SCREEN_HEIGHT))
	, m_win(Point(0, 0), Size(SCREEN_WIDTH, SCREEN_HEIGHT))
	, m_cursor(0, 0)
	, m_font(&PropFont::font)
	, m_fg(0xffff)
	, m_bg(0)
{
	uint offset = pio_add_program(pio, &st7789_lcd_program);
	st7789_lcd_program_init(pio, sm, offset, Mosi, Clk, SERIAL_CLK_DIV);

	gpio_init(CS);
	gpio_init(DC);
	gpio_init(Res);
	gpio_init(BL);
	gpio_set_dir(CS, GPIO_OUT);
	gpio_set_dir(DC, GPIO_OUT);
	gpio_set_dir(Res, GPIO_OUT);
	gpio_set_dir(BL, GPIO_OUT);

	gpio_put(CS, 1);
	gpio_put(Res, 1);
	init();
	gpio_put(BL, 1);

	clear();
	gpio_set_dir(BL, GPIO_OUT);
	gpio_set_function(BL, GPIO_FUNC_PWM);
	slice_num = pwm_gpio_to_slice_num(BL);
	pwmCh = pwm_gpio_to_channel(BL);
	const uint16_t kHz8 = 15630;
	kHz16 = kHz8 / 2;
	pwm_set_wrap(slice_num, kHz16);
	pwm_set_chan_level(slice_num, pwmCh, kHz16);
	pwm_set_enabled(slice_num, true);
	setBl(99);
	cout << "PWM pin=" << BL << " kHz16=" << kHz16 << " slice=" << slice_num << " ch=" << pwmCh << endl;
}

void St7789::clear(uint16_t color)
{
	setWindow(m_screenWin);
	startPixels();
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; ++i)
	{
		put(color);
	}
}

void St7789::fillRect(const Rect &r, uint16_t color)
{
	setWindow(r);
	startPixels();
	const uint16_t npix = r.area();
	for (uint i = 0; i < npix; ++i)
	{
		put(color);
	}
	setDcCs(1, 1);
}

void St7789::setDcCs(bool dc, bool cs)
{
	sleep_us(1);
	gpio_put_masked((1u << DC) | (1u << CS), !!dc << DC | !!cs << CS);
	sleep_us(1);
}

void St7789::writeCmd(const uint8_t *cmd, size_t count)
{
	st7789_lcd_wait_idle(pio, sm);
	setDcCs(0, 0);
	st7789_lcd_put(pio, sm, *cmd++);
	if (count >= 2)
	{
		st7789_lcd_wait_idle(pio, sm);
		setDcCs(1, 0);
		for (size_t i = 0; i < count - 1; ++i)
		{
			st7789_lcd_put(pio, sm, *cmd++);
		}
	}
	st7789_lcd_wait_idle(pio, sm);
	setDcCs(1, 1);
}

void St7789::writeCmd(const uint8_t cmd)
{
	st7789_lcd_wait_idle(pio, sm);
	setDcCs(0, 0);
	st7789_lcd_put(pio, sm, cmd);
	st7789_lcd_wait_idle(pio, sm);
	setDcCs(1, 0);
}



void St7789::setWindow(const Rect &r)
{
	if (m_win != r)
	{
		m_win = r;
		writeCmd(0x2A);
		put(m_win.left());
		put(m_win.right());
		setDcCs(1, 1);
		writeCmd(0x2B);
		put(m_win.top());
		put(m_win.bottom());
		setDcCs(1, 1);
	}
}

void St7789::init()
{
	// Format: cmd length (including cmd byte), post delay in units of 5 ms, then cmd payload
	// Note the delays have been shortened a little
	static const uint8_t st7789InitSeq[] =
	{
		1, 20, 0x01,                         // Software reset
		1, 10, 0x11,                         // Exit sleep mode
		2, 2, 0x3a, 0x55,                   // Set colour mode to 16 bit
		2, 0, 0x36, 0x00,                   // Set MADCTL: row then column, refresh is bottom to top ????
		5, 0, 0x2a, 0x00, 0x00, SCREEN_WIDTH>>8, SCREEN_WIDTH&0xff, // CASET: column addresses from 0 to 240 (f0)
		5, 0, 0x2b, 0x00, 0x00, SCREEN_HEIGHT>>8, SCREEN_HEIGHT&0xff, // RASET: row addresses from 0 to 240 (f0)
		1, 2, 0x21,                         // Inversion on, then 10 ms delay (supposedly a hack?)
		1, 2, 0x13,                         // Normal display on, then 10 ms delay
		1, 2, 0x29,                         // Main screen turn on, then wait 500 ms
		0                                     // Terminate list
	};
	const uint8_t *cmd = st7789InitSeq;
	while (*cmd)
	{
		writeCmd(cmd + 2, *cmd);
		sleep_ms(*(cmd + 1) * 5);
		cmd += *cmd + 2;
	}
}

void St7789::startPixels()
{
	uint8_t cmd = 0x2c; // RAMWR
	writeCmd(&cmd, 1);
	setDcCs(1, 0);
}

void St7789::put(uint8_t d)
{
	st7789_lcd_put(pio, sm, d);
}

void St7789::put(uint8_t *d, size_t count)
{
	while(count--)
	{
		put(*d++);
	}
}

void St7789::put(uint16_t *d, size_t count)
{
	while(count--)
	{
		put(*d++);
	}
}

void St7789::setBl(int v)
{
//	gpio_put(BL, on);
	blSet = kHz16 * v / 100;
	cout << __PRETTY_FUNCTION__ << ":" << v << " blSet=" << blSet << endl;
	pwm_set_chan_level(slice_num, pwmCh, blSet);
}

const float blFact = 1.1;

void St7789::blUp()
{
	blSet = (blSet * blFact) + 1;
	if (blSet >= kHz16)
	{
		blSet = kHz16 -1;
	}
	cout << __PRETTY_FUNCTION__ << " blSet=" << blSet << endl;
	pwm_set_chan_level(slice_num, pwmCh, blSet);
}

void St7789::blDown()
{
	blSet = (blSet / blFact) - 1;
	if (blSet <= 0)
	{
		blSet = 1;
	}
	cout << __PRETTY_FUNCTION__ << " blSet=" << blSet << endl;
	pwm_set_chan_level(slice_num, pwmCh, blSet);
}

void St7789::drawHLine(const Point &p, uint w, color_t color)
{
	fillRect(Rect(p, Size(w, 1)), color);
//	cout << __PRETTY_FUNCTION__ << ":" << hex << color << dec << p << w << endl;
}

void St7789::drawVLine(const Point &p, uint w, color_t color)
{
	fillRect(Rect(p, Size(1, w)), color);
//	cout << __PRETTY_FUNCTION__ << ":" << hex << color << dec << p << w << endl;
}

void St7789::drawRect(const Rect &r, color_t color)
{
	drawHLine(r.tl(), r.width(), color);
	drawHLine(r.tl() + Point(0, r.height()), r.width(), color);
	drawVLine(r.tl(), r.height(), color);
	drawVLine(r.tl() + Point(r.width(), 0), r.height(), color);
}

void St7789::drawChar(const Point &p, char c)
{
	if (! m_font)
	{
		cout << __PRETTY_FUNCTION__ << " no font" << endl;
		return;
	}
	if ((c < m_font->first()) || (c >= 0xff))
	{
		cout << __PRETTY_FUNCTION__ << " invalid char " << hex << int(c) << dec << endl;
		return;
	}
	const Rect r(p, m_font->charSize());
	setWindow(r);
	startPixels();
	uint8_t mask = m_font->reverse() ? 0x80 : 0x01;
	const uint8_t *bytes = m_font->charBytes(c);
	for (int i = 0; i < m_font->pixc(); ++i)
	{
		put(*bytes & mask ? m_fg : m_bg);
		if (m_font->reverse())
		{
			mask >>= 1;
			if (mask == 0)
			{
				++bytes;
				mask = 0x80;
			}
		}
		else
		{
			mask <<= 1;
			if (mask == 0)
			{
				++bytes;
				mask = 0x01;
			}
		}
	}
	st7789_lcd_wait_idle(pio, sm);
	setDcCs(1, 1);
	m_cursor = r.tr() + Point(1, 0);
}

void St7789::drawChar(char c)
{
	drawChar(m_cursor, c);
	if (m_cursor.x() >= SCREEN_WIDTH)
	{
		m_cursor.setX(0);
		m_cursor.setY(m_cursor.y() + m_font->h());
	}
}

void St7789::drawString(const char *s)
{
	while (*s)
	{
		switch (*s)
		{
		case '\r':
		case '\n':
			m_cursor.setX(0);
			m_cursor.setY(m_cursor.y() + m_font->h());
			break;
		default:
			drawChar(*s);
			break;
		}
		++s;
	}
}

static const color_t rainbowcolors[] =
{
	0xffff, 0x0000, 0x001f, 0x03ff,
	0x07ff, 0x07e0, 0x7fe0, 0xefe0,
	0xfbe0, 0xf800, 0xf80f, 0xf81f,
	0x7c1f, 0x001f
};

void St7789::rainbow()
{
	const int n = sizeof(rainbowcolors) / sizeof(rainbowcolors[0]);
	uint16_t w = SCREEN_WIDTH / n;
	int d = (SCREEN_WIDTH - (w * n)) / 2;
	for (int i = 0; i < n; ++i)
	{
		const Rect r(Point(0, d + i * w), Size(SCREEN_HEIGHT, w));
		fillRect(r, rainbowcolors[i]);
	}
}

Size St7789::charSize() const
{
	if (! m_font)
	{
		cout << __PRETTY_FUNCTION__ << " no font" << endl;
		return Size();
	}
	return m_font->charSize();
}

Size St7789::charSize(const char *s) const
{
	// this assumes a fixed font;
	if (! m_font)
	{
		cout << __PRETTY_FUNCTION__ << " no font" << endl;
		return Size();
	}
	Rect r;
	const Size cs(m_font->charSize());
	int h = cs.h(), w = 0, maxw = 0;
	while (*s)
	{
		Point tl;
		switch (*s)
		{
		case '\r':
		case '\n':
			h += cs.h();
			w = 0;
			break;
		default:
			w += cs.w();
			if (maxw < w)
			{
				maxw = w;
			}
			break;
		}
		++s;
	}
	return Size(maxw, h);
}


