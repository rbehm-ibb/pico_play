// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 10/31/2022 by behm
// ******************************************************

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "../ibblib/debug.h"
#include "../ibblib/ledblink.h"
#include "../ibblib/gpioinit.h"
#include "dwg.h"

using namespace std;

const char version[] = "Dwg 0.1";
 static const IoDef io[] =
 {
	 { 0, IoDef::In, 1, IoDef::PUp, "Clk" },
	 { 1, IoDef::In, 1, IoDef::PUp, "Dt" },
	 { 2, IoDef::In, 1, IoDef::PUp, "Sw" },
	 { -1, IoDef::In, 0, IoDef::None, nullptr }
 };
 GpioInit gpio(io);

static void uif();

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
	Dwg dwg(0, 1, 2);

	int n = 0;
	while (1)
	{
		blink.poll();
		dwg.poll();
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
	}
}
