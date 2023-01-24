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

const char version[] = "Servo 0.1";
 static const IoDef io[] =
 {
	 { 0, IoDef::Out, 1, IoDef::PUp, "Tx" },
	 { 24, IoDef::Out, 1, IoDef::None, "Led1" },
	 { 25, IoDef::Out, 1, IoDef::None, "Led2" },
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
	cout << "LED " << PICO_DEFAULT_LED_PIN << endl;

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
	}
}
