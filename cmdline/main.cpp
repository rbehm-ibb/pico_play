// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 10/31/2022 by behm
// ******************************************************

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "debug.h"
#include "ledblink.h"
#include "gpioinit.h"
#include "cmdline.h"

using namespace std;

const char version[] = "CmdLine 0.2";
static const IoDef io[] =
{
	{ 26, IoDef::Out, 0, IoDef::PUp, "A0" },
	{ 27, IoDef::Out, 0, IoDef::PUp, "A1" },
	{ 28, IoDef::Out, 0, IoDef::PUp, "A2" },
	{ 29, IoDef::Out, 0, IoDef::PUp, "A3" },
	{ 4, IoDef::Out, 0, IoDef::PUp, "SDA" },
	{ 5, IoDef::Out, 0, IoDef::PUp, "SCL" },
	{ 6, IoDef::Out, 1, IoDef::PUp, "Tx" },
	{ 7, IoDef::Out, 0, IoDef::PUp, "Rx" },
	{ 8, IoDef::Out, 0, IoDef::PUp, "SCK" },
	{ 9, IoDef::Out, 0, IoDef::PUp, "Miso" },
	{ 10, IoDef::Out, 0, IoDef::PUp, "Mosi" },
	{ 11, IoDef::Out, 0, IoDef::PUp, "NeoPwr" },
	{ 15, IoDef::Out, 0, IoDef::PUp, "NeoPix" },
	{ PICO_LED_R, IoDef::Out, 1, IoDef::None, "LedR" },
	{ PICO_LED_G, IoDef::Out, 1, IoDef::None, "LedG" },
	{ PICO_LED_B, IoDef::Out, 1, IoDef::None, "LedB" },
	{ -1, IoDef::In, 0, IoDef::None, nullptr }
};
GpioInit gpio(io);

static void uif();
LedBlink *blink = 0;
int main()
{
	stdio_usb_init();
	gpio.init();
//	gpio_set_function(0, GPIO_FUNC_UART);
//	gpio_set_function(1, GPIO_FUNC_UART);
//	uart_init(uart0, 38400);
	LedBlink _blink(PICO_LED_B, 100);
	LedBlink blinkG(PICO_LED_G, 200);
	LedBlink blinkR(PICO_LED_R, 150);
	blink = &_blink;
	while (! stdio_usb_connected())
	{
		blink->poll();
	}
	blink->setTime(300);
	Debug::showSysInfo(version);
	cout << "LED " << PICO_DEFAULT_LED_PIN << endl;

	while (1)
	{
		blinkG.poll();
		blinkR.poll();
		uif();
	}
}

static void  info(const CmdLine::Args &)
{
	Debug::showSysInfo(version);
//	cout << __PRETTY_FUNCTION__ << a << endl;
}

static void  showio(const CmdLine::Args &)
{
	gpio.showGpio();
//	cout << __PRETTY_FUNCTION__ << a << endl;
}

static void  led(const CmdLine::Args &a)
{
//	cout << __PRETTY_FUNCTION__ << a << endl;
	int a1 = a.num(1, 16);
	cout << "led " << a1 << endl;
	blink->setTime(a1);
}

static void  pin(const CmdLine::Args &a)
{
	cout << __PRETTY_FUNCTION__ << a << endl;
	int a1 = a.num(1);
	int a2 = a.num(2);
	cout << "pin " << a1 << ',' << a2 << endl;
	gpio_put(a1, a2);
}

static void uif()
{
	static const CmdLine::Cmd cmd[] =
	{
		{ "info", info },
		{ ".", showio  },
		{ "led", led },
		{ "pin", pin },
		{ nullptr, nullptr }
	};

	static CmdLine cmdline(cmd);
	int a1, a2, a3;
	blink->poll();
	cmdline.poll();
	return;
}
