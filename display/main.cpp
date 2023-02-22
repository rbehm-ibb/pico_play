// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 10/31/2022 by behm
// ******************************************************

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <bit>
//#include "pico/stdlib.h"
//#include "hardware/gpio.h"
#include "gpioinit.h"
#include "debug.h"
#include "ledblink.h"

#include "ibpoint.h"
#include "ibrect.h"
#include "spihw.h"

using namespace std;

const char version[] = "IbDisp 0.1";

enum DisplayPins { Res=0, Cs=1, Clk=2, Mosi=3, Cd=5, Bl=6 };
static const IoDef io[] =
{
	{ Res, IoDef::Out, 1, IoDef::None, "Res" },
	{ Cs, IoDef::Out, 1, IoDef::None, "/CS" },
	{ Clk, IoDef::Out, 1, IoDef::None, "Clk" },
	{ Mosi, IoDef::Out, 1, IoDef::None, "Mosi" },
	{ 4, IoDef::In,  1, IoDef::PUp, "Miso" },
	{ Cd, IoDef::Out, 1, IoDef::None, "C/D" },
	{ Bl, IoDef::Out, 1, IoDef::None, "BL" },
	{ PICO_DEFAULT_LED_PIN,IoDef::Out, 1, IoDef::None, "LED"  },
	{ -1, IoDef::Out, 0, IoDef::None, nullptr }
};

GpioInit gpio(io);

static void uif();
SpiHw *ibSpi1 = 0;

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
	gpio.showGpio();
	ibSpi1 = new SpiHw(SpiHw::hwSpi0); // PICO_DEFAULT_SPI_CSN_PIN, 5, 6);
	ibSpi1->start();

//	int n = 0;
	while (1)
	{
		blink.poll();
		uif();
	}
}

static void uif()
{
	static const uint8_t dv[] = { 0x11, 0x22, 0x55 };
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
	case 'e':
		cout << "Endian=" << __BYTE_ORDER__ << " big=" <<__ORDER_BIG_ENDIAN__ << " little=" << __ORDER_LITTLE_ENDIAN__  << endl;
	{
		uint16_t u16 = 0x1234;
		uint32_t u32 = 0x12345678;
		Debug::dump((uint8_t*)&u16, 2);
		Debug::dump((uint8_t*)&u32, 4);
	}
		break;
	case 'r':
	{
		IbRect r(IbPoint(1, 2), IbSize(3, 4));
		cout << r << " S="  << r.size() << endl;
		IbPoint p(10, 20);
		IbSize sz = r.size();
		r.moveBy(p);
		cout << r << r.tl() + r.br() << sz << endl;
		r.setSize(IbSize(5, 5));
		sz += 7;
		cout << r << "#" << sizeof(r) << " " << p << '#' << sizeof(p) << ' ' << sz << '#' << sizeof(sz) << endl;
		cout << r << endl;
		r += 2;
		cout << "+2 " << r << endl;
		r += -4;
		cout << "-4 " << r << endl;
		cout << sz;
		sz *= 2;
		cout << "*2 " << sz << endl;
		sz *= 1.1f;
		cout << "*1.1 " << sz << endl;
		sz += -1;
		cout << "-1 " << sz << endl;
	}
	case 'w':
		ibSpi1->csOn();
		ibSpi1->tx((uint16_t)0x5555);
		ibSpi1->csOff();
		break;
	case 'W':
		ibSpi1->tx(0x12, dv, count_of(dv));
		break;
	break;
	}
}
