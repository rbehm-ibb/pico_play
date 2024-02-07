// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 10/31/2022 by behm
// ******************************************************

#include <ostream>
#include <iomanip>
#include <string.h>
// #include <hardware/i2c.h>
#include "debug.h"
#include "ledblink.h"
#include "gpioinit.h"
#include "cmdline.h"
#include <pico/binary_info.h>
#include "i2cchannel.h"
#include "i2cscan.h"
#include "i2cdevice.h"
#include "i2cregister.h"

using namespace std;

const char version[] = "LM75 0.1";
static const IoDef io[] =
{
	{ 0, IoDef::Out, 1, IoDef::PUp, "Tx0" },
	{ 1, IoDef::In, 0, IoDef::PUp, "Rx0" },
	{ 2, IoDef::In, 0, IoDef::PUp, "tgl" },
	{ 3, IoDef::In, 0, IoDef::PUp, "irq" },
	{ PICO_DEFAULT_I2C_SDA_PIN, IoDef::In, 0, IoDef::PUp, "SDA" },
	{ PICO_DEFAULT_I2C_SCL_PIN, IoDef::In, 0, IoDef::PUp, "SCL" },
	{ PICO_DEFAULT_SPI_SCK_PIN, IoDef::In, 0, IoDef::PUp, "SCK" },
	{ PICO_DEFAULT_SPI_RX_PIN, IoDef::In, 0, IoDef::PUp, "Miso" },
	{ PICO_DEFAULT_SPI_TX_PIN, IoDef::In, 0, IoDef::PUp, "Mosi" },
	{ PICO_DEFAULT_WS2812_POWER_PIN, IoDef::In, 0, IoDef::PUp, "NeoPwr" },
	{ PICO_DEFAULT_WS2812_PIN, IoDef::In, 0, IoDef::PUp, "NeoPix" },
	{ 26, IoDef::In, 0, IoDef::PUp, "A0" },
	{ 27, IoDef::In, 0, IoDef::PUp, "Button" },
	{ 28, IoDef::In, 0, IoDef::PUp, "A2" },
	{ 29, IoDef::In, 0, IoDef::PUp, "A3" },
	{ 20, IoDef::In, 0, IoDef::PUp, "Tx1" },
	{ 21, IoDef::In, 0, IoDef::PUp, "Rx1" },
#ifdef PICO_LED_G
	{ PICO_LED_R, IoDef::Out, 1, IoDef::None, "LedR" },
	{ PICO_LED_G, IoDef::Out, 1, IoDef::None, "LedG" },
	{ PICO_LED_B, IoDef::Out, 1, IoDef::None, "LedB" },
#endif
	{ -1, IoDef::In, 0, IoDef::None, nullptr }
};
GpioInit gpio(io);

static void uif();
static void scanI2c(const CmdLine::Args &a);
static void getlm(const CmdLine::Args &a);
bool reserved_addr(uint8_t addr)
{
	return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}
LedBlink *blink = 0;

I2cChannel *chan;

int main()
{
	stdio_usb_init();
	gpio.init();

	LedBlink _blink(PICO_DEFAULT_LED_PIN, 100);
#ifdef PICO_LED_G
	// LedBlink blinkG(PICO_LED_G, 200);
#endif
#ifdef PICO_LED_R
	// LedBlink blinkR(PICO_LED_R, 150);
#endif
	blink = &_blink;
	while (! stdio_usb_connected())
	{
		blink->poll();
	}
	blink->setTime(300);
	Debug::showSysInfo(version);
	chan =  new I2cChannel (i2c_default, PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN);
	gpio.showGpio();
	// i2c_init(i2c_default, 100 * 1000);
	// gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
	// gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
	// gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
	// gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
	// bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

	while (1)
	{
		_blink.poll();
#ifdef PICO_LED_G
		// blinkG.poll();
#endif
#ifdef PICO_LED_R
		// blinkR.poll();
#endif
		uif();
//		rx();
	}
}

static void  info(const CmdLine::Args &)
{
	Debug::showSysInfo(version);
	Debug::heapInfo();
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
	int a1 = a.num(1, 10);
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
		{ "s", scanI2c},
		{ "t", getlm},
		{ nullptr, nullptr }
	};

	static CmdLine cmdline(cmd);
	// rx();
	cmdline.poll();
	if (gpio_get(27) == 0)
	{
		CmdLine::Args args;
		getlm(args);
		while (gpio_get(27) == 0)
			;
	}
	return;
}

static void scanI2c(const CmdLine::Args &a)
{
	I2cScan scan(chan);
	scan.scan();
}

static void getlm(const CmdLine::Args &/*a*/)
{
	I2cDevice lm75(chan, 0x48);
	I2cRegister temp(&lm75, 0, 2);
	I2cRegister temp1(&lm75, 0, 1);
	uint16_t t16 = lm75.readReg16(0);
	cout << " regTemp16="  << temp.read() /256. << " reg8=" << temp1.read() << endl;
}

