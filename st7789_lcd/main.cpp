// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/30/2022 by behm
// ******************************************************

/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Newly started version (c) 2022, RBehm
 */

#include <stdio.h>
#include <iostream>
// #include "pico/stdlib.h"
#include "hardware/adc.h"
#include "ibblib/debug.h"
#include "ibblib/ledblink.h"
#include "ibblib/gpioinit.h"
#include "st7789.h"
#include "propfont.h"
#include "font8x16.h"

static const IoDef io[] =
{
	{ DC, IoDef::Out, 1, IoDef::None, "D/C" },
	{ CS, IoDef::Out, 1, IoDef::None, "/CS" },
	{ Clk, IoDef::Out, 1, IoDef::None, "Clk" },
	{ Mosi, IoDef::Out, 1, IoDef::None, "Mosi" },
	{ Miso, IoDef::In,  1, IoDef::PUp, "Miso" },
	{ Res, IoDef::Out, 1, IoDef::None, "Res" },
	{ BL, IoDef::Out, 1, IoDef::None, "BL" },
	{ PICO_DEFAULT_LED_PIN,IoDef::Out, 1, IoDef::None, "LED"  },
	{ -1, IoDef::Out, 0, IoDef::None, nullptr }

};

static void raster(St7789 *lcd);

const char *version = "Driver for ST7789 using fast spi via PIO 0.1d1";
GpioInit gpio(io);

int main()
{
//	stdio_init_all();
	stdio_usb_init();
	LedBlink blink(PICO_DEFAULT_LED_PIN, 70);
	while (! stdio_usb_connected())
	{
		blink.poll();
	}
	blink.setTime(300);
	gpio.init();
	Debug::showSysInfo(version);
	St7789 lcd;
	gpio.showGpio();
	for (;;)
	{
		blink.poll();
		raster(&lcd);
		int c = getchar_timeout_us(0);
		if (c < 0)
		{
			continue;
		}
		cout << " kbd:" << char(c) << endl;
		switch (c)
		{
		case '.':
			Debug::showSysInfo(version);
			gpio.showGpio();
			break;
		case 't':
		{
			adc_init();
			adc_set_temp_sensor_enabled(true);
			adc_select_input(4);
			int adc =  adc_read();
			float ADC_voltage = adc * (3.3 / (4095.));
			float temperature_celcius = 27 - (ADC_voltage - 0.706) / 0.001721;
			printf("ADC=%d ADC-V=%.1fV T=%.1fC\n", adc, ADC_voltage, temperature_celcius);
		}
		break;
		case 'T':
			blink.setTime(100);
//			lcd.clear();
			do
			{
				int adc =  adc_read();
				float ADC_voltage = adc * (3.3 / (4095.));
				float temperature_celcius = 27 - (ADC_voltage - 0.706) / 0.001721;
				char s[20];
				sprintf(s, "%5.1fC", temperature_celcius);
				lcd.setBg(St7789::BLACK);
				lcd.setFg(St7789::RED);
				lcd.setCursor(50, 120);
				Point p = lcd.cursor() + Point(-1, -1);
				Rect r = Rect(p, lcd.charSize(s));
				r += Size(1, 1);
				r.setTl(p);
				lcd.drawRect(r, St7789::PINK);
				lcd.drawString(s);
				blink.poll();
			}
			while (getchar_timeout_us(100000) < 0);
			break;
		case '0':
			lcd.setBl(false);
			break;
		case '1':
			lcd.setBl(true);
			break;
		case 'c':
			lcd.clear(rgb565(63, 63, 0));
			cout << lcd.screen() << " A=" << lcd.screen().area() << endl;
//			sleep_ms(1000);
			break;
		case 'w':
			lcd.clear(0xffff);
//			sleep_ms(1000);
			break;
		case 'r':
			lcd.clear();
			{
				Rect r(Point(0, 0), Size(19, 19));
				for (int i = 0; i <= 240 - 20; i += 20)
				{
					lcd.fillRect(r, rgb565(31, 0, 0));
					lcd.drawRect(r, 0xffff);
					r += Point(20, 20);
				}
			}
			cout << lcd.screen() << " A=" << lcd.screen().area() << endl;
//			sleep_ms(1000);
			break;
		case 'R':
			lcd.clear();
			lcd.rainbow();
//			sleep_ms(1000);
			break;
		case 'l':
			lcd.clear();
			for (int i = 0; i < 24; ++i)
			{
				lcd.drawHLine(Point(0, i * 10), 240, rgb565(31, 63, i * 31 / 24));
			}
			break;
		case 'L':
			lcd.clear();
			for (int i = 0; i < 24; ++i)
			{
				lcd.drawVLine(Point(i * 10, 0), 240, rgb565(31, 63, i * 31 / 24));
			}
			break;
		case 'C':
			lcd.drawChar(Point(10, 10), 'G');
			break;
		case 's':
			lcd.clear();
			lcd.setFg(rgb565(31, 0, 0));
			lcd.setBg(rgb565(0, 63, 31));
		{
			lcd.setCursor(1, 1);
			const char s[] = "ABCDEFGHIJKL\n0123456789"; // \nabcdefghijklmnopqrstuvwxyz@\n! \"$%&/()=?`´~#’-.,;:_<>|\\^";
			Point p = lcd.cursor() + Point(-1, -1);
			Rect r = Rect(p, lcd.charSize(s));
			r += Size(1, 1);
			r.setTl(p);
			lcd.drawString(s);
			lcd.drawRect(r, rgb565(31, 63, 31));
			cout << p << r << lcd.win() << "A=" << lcd.win().area() << endl;
		}
			break;
		case 'S':
			cout << lcd.charSize("ABCDE\nFGHIJ");
			break;
		case 'p':
			lcd.setCursor(Point(0, 0));
			lcd.setFont(&Font8x16::font);
			break;
		case 'P':
			lcd.setCursor(Point(0, 0));
			lcd.setFont(&PropFont::font);
			break;

		}
	}
}

static void raster(St7789 *lcd)
{
	const int dist = 10;
	const int w = lcd->screen().width();
	const int h = lcd->screen().height();
	for (int i = 0; i < w; i += dist)
	{
		lcd->drawVLine(Point(i, 0), h, St7789::WHITE);
	}
	for (int i = 0; i < h; i += dist)
	{
		lcd->drawHLine(Point(0, i), w, St7789::WHITE);
	}
}