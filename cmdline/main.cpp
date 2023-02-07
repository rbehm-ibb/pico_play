// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 10/31/2022 by behm
// ******************************************************

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
//#include "hardware/gpio.h"
#include "../ibblib/debug.h"
#include "../ibblib/ledblink.h"
#include "../ibblib/gpioinit.h"
#include "cmdline.h"

using namespace std;

const char version[] = "CmdLine 0.1";
static const IoDef io[] =
{
	{ 0, IoDef::Out, 1, IoDef::PUp, "Tx" },
	{ 1, IoDef::Out, 0, IoDef::PUp, "Rx" },
	{ 24, IoDef::Out, 1, IoDef::None, "Led1" },
	{ 25, IoDef::Out, 1, IoDef::None, "Led2" },
	{ -1, IoDef::In, 0, IoDef::None, nullptr }
};
GpioInit gpio(io);

static void uif();
LedBlink *led = 0;
int main()
{
	stdio_usb_init();
	gpio.init();
//	gpio_set_function(0, GPIO_FUNC_UART);
//	gpio_set_function(1, GPIO_FUNC_UART);
//	uart_init(uart0, 38400);
	LedBlink blink(PICO_DEFAULT_LED_PIN, 100);
	led = &blink;
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
	static const Cmd cmd[] =
	{
		{ 1, "info" },
		{ 2, "io" },
		{ 3, "led" },
		{ 4, "pin" },
		{ 0, nullptr },
	};

	static CmdLine cmdline(cmd);
	int a1, a2, a3;
	int cid = cmdline.poll();
	if (cid >= -1)
	{
		cout << "cmdline->"  << cid;
		auto arg = cmdline.args();
		for  (const char *s : arg)
		{
			cout << " T<" << s << ">";
		}
		cout << endl;
		switch (cid)
		{
		case 1:
			Debug::showSysInfo(version);
			break;
		case 2:
			gpio.showGpio();
			break;
		case 3:
			a1 = cmdline.num(1, 16);
			cout << "led " << a1 << endl;
			led->setTime(a1);
			break;
		case 4:
			a1 = cmdline.num(1);
			a2 = cmdline.num(2);
			cout << "pin " << a1 << ',' << a2 << endl;
			gpio_put(a1, a2);
			break;
		}
		cmdline.clear();
	}
}
