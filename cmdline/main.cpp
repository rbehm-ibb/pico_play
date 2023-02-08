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
static void rx();
static void on_uart_rx();
static /*volatile*/ queue_t rxq;

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

	queue_init(&rxq, sizeof(uint8_t), 30);

	// And set up and enable the interrupt handlers
	irq_set_exclusive_handler(UART0_IRQ, on_uart_rx);
	irq_set_enabled(UART0_IRQ, true);

	// Now enable the UART to send interrupts - RX only
	uart_set_irq_enables(uart0, true, false);

	while (1)
	{
//		blinkG.poll();
//		blinkR.poll();
		uif();
		rx();
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

static void  uartwrite(const CmdLine::Args &a)
{
	for (const char *s : a)
	{
		uart_puts(uart0, s);
		cout << __PRETTY_FUNCTION__ << " <" << s << ">" << endl;
	}
}


static void uif()
{
	static const CmdLine::Cmd cmd[] =
	{
		{ "info", info },
		{ ".", showio  },
		{ "led", led },
		{ "pin", pin },
		{ "w", uartwrite },
		{ nullptr, nullptr }
	};

	static CmdLine cmdline(cmd);
	blink->poll();
	cmdline.poll();
	return;
}

static volatile int chars_rxed = 0;

static void rx()
{
	static const uint32_t mask = 1U << 2;
	while (! queue_is_empty(&rxq))
	{
		gpio_set_mask(mask);
		char c;
		queue_remove_blocking(&rxq, &c);
		gpio_clr_mask(mask);
		cout << '<' << chars_rxed << '.' << hex << int(c) << dec << flush;
	}
}


// RX interrupt handler
void on_uart_rx()
{
	while (uart_is_readable(uart0))
	{
		uint8_t ch = uart_getc(uart0);
		queue_add_blocking(&rxq, &ch);
		gpio_xor_mask(1U << 3);
		chars_rxed++;
	}
}

