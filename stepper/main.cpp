// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 10/31/2022 by behm
// ******************************************************

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "../ibblib/debug.h"
#include "../ibblib/ledblink.h"
#include "../ibblib/gpioinit.h"

using namespace std;

const char version[] = "BiPol Stepper 0.1";
static const IoDef io[] =
{
	{ 0, IoDef::Out, 0, IoDef::None, "StA+" },
	{ 1, IoDef::Out, 0, IoDef::None, "StB+" },
	{ 2, IoDef::Out, 0, IoDef::None, "StA-" },
	{ 3, IoDef::Out, 0, IoDef::None, "StB-" },
	{ 4, IoDef::Out, 0, IoDef::None, "Slp" },
	{ -1, IoDef::In, 0, IoDef::None, nullptr }
};
GpioInit gpio(io);

static void uif();

static int istep = -1;
static void stepf();
static void stepb();
static void step();

int main()
{
	stdio_usb_init();
	gpio.init();
	LedBlink blink(PICO_DEFAULT_LED_PIN, 100);
	while (! stdio_usb_connected())
	{
		blink.poll();
	}
	blink.setTime(300);
	Debug::showSysInfo(version);

	int n = 0;
	while (1)
	{
		blink.poll();
		uif();
	}
}

static void uif()
{
	const int c = getchar_timeout_us(0);
	if (c < 0)
		return;
	printf("rx=%04x\n", c);
	switch (c)
	{
	case '.':
		Debug::showSysInfo(version);
		gpio.showGpio();
		break;
	case 's':
		gpio_put(4, 0);
		break;
	case 'S':
		gpio_put(4, 1);
		break;
	case '0':
		istep = -1;
		step();
		break;
	case '+':
		stepf();
		break;
	case '-':
		stepb();
		break;
	}
}

static void stepf()
{
	if (++istep > 3)
	{
		istep = 0;
	}
	step();
}

static void stepb()
{
	if (--istep < 0)
	{
		istep = 3;
	}
	step();
}

static void step()
{
	switch (istep)
	{
	case 0:
		gpio_put(0, 1);
		gpio_put(1, 0);
		gpio_put(2, 0);
		gpio_put(3, 0);
		break;
	case 1:
		gpio_put(0, 0);
		gpio_put(1, 1);
		gpio_put(2, 0);
		gpio_put(3, 0);
		break;
	case 2:
		gpio_put(0, 0);
		gpio_put(1, 0);
		gpio_put(2, 1);
		gpio_put(3, 0);
		break;
	case 3:
		gpio_put(0, 0);
		gpio_put(1, 0);
		gpio_put(2, 0);
		gpio_put(3, 1);
		break;
	default:
		gpio_put(0, 0);
		gpio_put(1, 0);
		gpio_put(2, 0);
		gpio_put(3, 0);
		break;
	}
}

