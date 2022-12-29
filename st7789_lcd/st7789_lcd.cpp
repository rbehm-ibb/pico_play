/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <iostream>
#include <math.h>

#include "pico/stdlib.h"
//#include "hardware/gpio.h"
#include "hardware/interp.h"
#include "ibblib/debug.h"
#include "ibblib/ledblink.h"

#include "st7789.h"
#include "raspberry_256x256_rgb565.h"

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240
#define IMAGE_SIZE 256
#define LOG_IMAGE_SIZE 8

const char *version = "ST7789 via pio";
int main()
{
//	stdio_init_all();
	stdio_usb_init();
	LedBlink blink(PICO_DEFAULT_LED_PIN, 70);
	St7789 lcd;
	while (! stdio_usb_connected())
	{
		blink.poll();
	}
	blink.setTime(300);
	Debug::showSysInfo(version);

	// Other SDKs: static image on screen, lame, boring
	// Raspberry Pi Pico SDK: spinning image on screen, bold, exciting

	// Lane 0 will be u coords (bits 8:1 of addr offset), lane 1 will be v
	// coords (bits 16:9 of addr offset), and we'll represent coords with
	// 16.16 fixed point. ACCUM0,1 will contain current coord, BASE0/1 will
	// contain increment vector, and BASE2 will contain image base pointer
#define UNIT_LSB 16
	interp_config lane0_cfg = interp_default_config();
	interp_config_set_shift(&lane0_cfg, UNIT_LSB - 1); // -1 because 2 bytes per pixel
	interp_config_set_mask(&lane0_cfg, 1, 1 + (LOG_IMAGE_SIZE - 1));
	interp_config_set_add_raw(&lane0_cfg, true); // Add full accumulator to base with each POP
	interp_config lane1_cfg = interp_default_config();
	interp_config_set_shift(&lane1_cfg, UNIT_LSB - (1 + LOG_IMAGE_SIZE));
	interp_config_set_mask(&lane1_cfg, 1 + LOG_IMAGE_SIZE, 1 + (2 * LOG_IMAGE_SIZE - 1));
	interp_config_set_add_raw(&lane1_cfg, true);

	interp_set_config(interp0, 0, &lane0_cfg);
	interp_set_config(interp0, 1, &lane1_cfg);
	interp0->base[2] = (uint32_t) raspberry_256x256;

	float theta = 0.f;
	float theta_max = 2.f * (float) M_PI;
	while (1)
	{
		theta += 0.02f;
		if (theta > theta_max)
			theta -= theta_max;
		int32_t rotate[4] =
		{
			(int32_t)(cosf(theta) *(1 << UNIT_LSB)), (int32_t)(-sinf(theta) *(1 << UNIT_LSB)),
			(int32_t)(sinf(theta) *(1 << UNIT_LSB)), (int32_t)(cosf(theta) *(1 << UNIT_LSB))
		};
		interp0->base[0] = rotate[0];
		interp0->base[1] = rotate[2];
		lcd.startPixels();
		for (int y = 0; y < SCREEN_HEIGHT; ++y)
		{
			interp0->accum[0] = rotate[1] * y;
			interp0->accum[1] = rotate[3] * y;
			for (int x = 0; x < SCREEN_WIDTH; ++x)
			{
				uint16_t colour = *(uint16_t *) (interp0->pop[2]);
				lcd.put(colour);
			}
		}
		blink.poll();
		int c = getchar_timeout_us(0);
		if (c < 0)
		{
			continue;
		}
		cout << " kbd:" << char(c) << endl;
		switch (c)
		{
		case 'v':
			Debug::showSysInfo(version);
			break;
		case 'x':
			Debug::showGpio();
			break;
		case '0':
			lcd.setBl(false);
			break;
		case '1':
			lcd.setBl(true);
			break;
		case 'c':
			lcd.clear();
			cout << lcd.screen() << endl;
			sleep_ms(1000);
			break;
		case 'w':
			lcd.clear(0xffff);
			sleep_ms(1000);
			break;
		case 'r':
			lcd.clear();
			lcd.fillRect(Rect(Point(0, 0), Size(20, 30)), 0xffff);
			cout << lcd.screen() << " A=" << lcd.screen().area() << endl;
			sleep_ms(1000);
			lcd.setFullScreen();
			break;
		}
	}
}
