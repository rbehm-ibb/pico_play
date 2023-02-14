// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 10/31/2022 by behm
// ******************************************************

#include <ostream>
#include <stdlib.h>
#include <stdio.h>
//#include "pico/stdlib.h"
//#include "pico/util/queue.h"
//#include "hardware/irq.h"
#include "debug.h"
#include "ledblink.h"
#include "gpioinit.h"
#include "cmdline.h"
#include "simpleuart.h"
#include "uartline.h"
#include "uartipc.h"
#include "timer.h"

using namespace std;

const char version[] = "UartIpc 0.1";
static const IoDef io[] =
{
	{ 0, IoDef::Out, 1, IoDef::PUp, "Tx0" },
	{ 1, IoDef::In, 0, IoDef::PUp, "Rx0" },
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
	{ 20, IoDef::Out, 0, IoDef::PUp, "Tx1" },
	{ 21, IoDef::Out, 0, IoDef::PUp, "Rx1" },
#ifdef PICO_LED_G
	{ PICO_LED_R, IoDef::Out, 1, IoDef::None, "LedR" },
	{ PICO_LED_G, IoDef::Out, 1, IoDef::None, "LedG" },
	{ PICO_LED_B, IoDef::Out, 1, IoDef::None, "LedB" },
#endif
	{ -1, IoDef::In, 0, IoDef::None, nullptr }
};
GpioInit gpio(io);

static void uif();
static void rx();

LedBlink *blink = 0;
UartIpc *uart = nullptr;
Timer *timer[3] = {  nullptr };

int main()
{
	stdio_usb_init();
	gpio.init();

	LedBlink _blink(PICO_DEFAULT_LED_PIN, 100);
#ifdef PICO_LED_G
	LedBlink blinkG(PICO_LED_G, 200);
#endif
#ifdef PICO_LED_R
	LedBlink blinkR(PICO_LED_R, 150);
#endif
	blink = &_blink;
	while (! stdio_usb_connected())
	{
		blink->poll();
	}
	blink->setTime(300);
	Debug::showSysInfo(version);

//	{
//		UartLine ul(0);
//		ul.setLeadin("1234567890qwert");
//	}

	uart = new UartIpc(0);
//	uart->setLeadout(">");
	cout << "uart" << uart->uartIdx() << " T" << uart->txPin() << " R" << uart->rxPin() << endl;
	for (int i = 0; i < count_of(timer); ++i)
	{
		timer[i] = new Timer;
		cout <<  "timer #" << timer[i]->id() << endl;
	}
	cout << "Uart:" << sizeof(UartBase) << " SimpleUart:" << sizeof(SimpleUart)
	     << " UartLine:" << sizeof(UartLine) << " UartIpc:" << sizeof(UartIpc)
		 << " Timer:" << sizeof(Timer)
	     << endl;
	while (1)
	{
#ifdef PICO_LED_G
		blinkG.poll();
#endif
#ifdef PICO_LED_R
		blinkR.poll();
#endif
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
	for (int i = 1; i < a.size(); ++i)
	{
		cout << __PRETTY_FUNCTION__ << " <" << a.argn(i) << ">" << endl;
		uart->put(a.asVecu8(i));
	}
}

static void  leadin(const CmdLine::Args &a)
{
	if (a.size() > 1)
	{
//		uart->setLeadin(a[1]);
	}
}

static void  leadout(const CmdLine::Args &a)
{
	if (a.size() > 1)
	{
//		uart->setLeadout(a[1]);
	}
}

static void  start(const CmdLine::Args &a)
{
	cout << __PRETTY_FUNCTION__ << endl;
	int i = a.num(1);
	if (i >= 0 && i < count_of(timer))
	{
		timer[i]->start();
	}
}

static void  stop(const CmdLine::Args &a)
{
	cout << __PRETTY_FUNCTION__ << a << endl;
	if (a.size() == 1)
	{
		for (int  i = 0; i < count_of(timer); ++i)
		{
			timer[i]->stop();
		}
		return;
	}
	int i = a.num(1);
	if (i >= 0 && i < count_of(timer))
	{
	timer[i]->stop();
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
		{ "lin", leadin },
		{ "lout", leadout },
		{ "start", &start },
		{ "stop", &stop },
		{ nullptr, nullptr }
	};

	static CmdLine cmdline(cmd);
	blink->poll();
	cmdline.poll();
	return;
}

static void rx()
{
	static int lasttick[count_of(timer)] = { 0 };
	static const uint32_t mask = 1U << 2;
	uart->poll();
	while (uart->hasRx())
	{
		std::vector<uint8_t> rxb =  uart->get();
		cout << __PRETTY_FUNCTION__ << " rx:" << rxb.size() << " <" << rxb.data() << ">" << endl;
	}
	for (int i = 0; i < count_of(timer); ++i)
	{
		int t = timer[i]->tick();
		if (lasttick[i] != t)
		{
			lasttick[i] = t;
			cout << "timer " << timer[i]->id() << " #" << t << endl;
		}


	}
}
