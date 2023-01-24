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

#include "point.h"
#include "rect.h"
#include "spi1.h"

using namespace std;

const char version[] = "IbDisp 0.1";
 static const IoDef io[] =
 {
	 { 0, IoDef::Out, 1, IoDef::PUp, "Tx" },
	 { 10, IoDef::Out, 1, IoDef::None, "D/C" },
	 { 11, IoDef::Out, 1, IoDef::None, "Res" },
	 { 13, IoDef::Out, 1, IoDef::None, "/Cs" },
	 { 12, IoDef::In,  0, IoDef::None, "Miso" },
	 { 14, IoDef::Out, 0, IoDef::None, "Sck" },
	 { 15, IoDef::Out,  0, IoDef::None, "Mosi" },
	 { 25, IoDef::Out, 1, IoDef::None, "Led2" },
	 { -1, IoDef::In, 0, IoDef::None, nullptr }
 };

 GpioInit gpio(io);
 Spi1 ibSpi1(13, 10, 11);

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
	ibSpi1.start();
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
	case 'r':
	{
		IbRect r(IbPoint(1,2), IbSize(3, 4));
		cout << r << " S="  << r.size() << endl;
		r.moveBy(IbPoint(10, 10));
		cout << r << r.tl() + r.br() << endl;
	}
		break;
	}
}
