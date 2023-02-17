// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 10/31/2022 by behm
// ******************************************************

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/util/queue.h"
#include "hardware/irq.h"
#include "debug.h"
#include "ledblink.h"
#include "gpioinit.h"
#include "cmdline.h"

using namespace std;

const char version[] = "CmdLine 0.2";
static const IoDef io[] =
{
	{ 0, IoDef::Out, 1, IoDef::PUp, "Tx" },
	{ 1, IoDef::Out, 0, IoDef::PUp, "Rx" },
	{ 2, IoDef::Out, 0, IoDef::PUp, "tgl" },
	{ 3, IoDef::Out, 0, IoDef::PUp, "irq" },
	{ 4, IoDef::Out, 0, IoDef::PUp, "SDA" },
	{ 5, IoDef::Out, 0, IoDef::PUp, "SCL" },
	{ 8, IoDef::Out, 0, IoDef::PUp, "SCK" },
	{ 9, IoDef::Out, 0, IoDef::PUp, "Miso" },
	{ 10, IoDef::Out, 0, IoDef::PUp, "Mosi" },
	{ 11, IoDef::Out, 0, IoDef::PUp, "NeoPwr" },
	{ 15, IoDef::Out, 0, IoDef::PUp, "NeoPix" },
	{ 26, IoDef::Out, 0, IoDef::PUp, "A0" },
	{ 27, IoDef::Out, 0, IoDef::PUp, "A1" },
	{ 28, IoDef::Out, 0, IoDef::PUp, "A2" },
	{ 29, IoDef::Out, 0, IoDef::PUp, "A3" },
//	{ PICO_LED_R, IoDef::Out, 1, IoDef::None, "LedR" },
//	{ PICO_LED_G, IoDef::Out, 1, IoDef::None, "LedG" },
//	{ PICO_LED_B, IoDef::Out, 1, IoDef::None, "LedB" },
	{ -1, IoDef::In, 0, IoDef::None, nullptr }
};
GpioInit gpio(io);

static void uif();

LedBlink *blink = 0;

int main()
{
	stdio_usb_init();
	gpio.init();
	uart_init(uart0, 9600);
	gpio_set_function(0, GPIO_FUNC_UART);
	gpio_set_function(1, GPIO_FUNC_UART);
	uart_set_hw_flow(uart0, false, false);
	// Set our data format
	uart_set_format(uart0, 8, 2, UART_PARITY_NONE);

	// Turn off FIFO's - we want to do this character by character
	uart_set_fifo_enabled(uart0, false);

	LedBlink _blink(PICO_DEFAULT_LED_PIN, 100);
//	LedBlink blinkG(PICO_LED_G, 200);
//	LedBlink blinkR(PICO_LED_R, 150);
	blink = &_blink;
	while (! stdio_usb_connected())
	{
		blink->poll();
	}
	blink->setTime(300);
	Debug::showSysInfo(version);


	// Now enable the UART to send interrupts - RX only
	uart_set_irq_enables(uart0, true, false);

	while (1)
	{
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

static void uif()
{
	static const CmdLine::Cmd cmd[] =
	{
		{ "info", info },
		{ ".", showio  },
		{ nullptr, nullptr }
	};

	static CmdLine cmdline(cmd);
	blink->poll();
	cmdline.poll();
	return;
}
