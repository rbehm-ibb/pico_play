// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 10/31/2022 by behm
// ******************************************************

#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "../ibblib/debug.h"
#include "../ibblib/ledblink.h"
#include "../ibblib/gpioinit.h"

const char version[] = "Test SPI 0.2";

static const IoDef io[] =
{
	{ 0, IoDef::Out, 1, IoDef::None, "D/C" },
	{ 1, IoDef::Out, 1, IoDef::None, "/CS" },
	{ 2, IoDef::Out, 1, IoDef::None, "Clk" },
	{ 3, IoDef::Out, 1, IoDef::None, "Mosi" },
	{ 4, IoDef::In,  1, IoDef::PUp, "Miso" },
	{ 5, IoDef::Out, 1, IoDef::None, "Res" },
	{ 6, IoDef::Out, 1, IoDef::None, "BL" },
	{ PICO_DEFAULT_LED_PIN,IoDef::Out, 1, IoDef::None, "LED"  },
	{ -1, IoDef::Out, 0, IoDef::None, nullptr }

};
static int rx();
static void uif();
#define PIN_MISO 4
#define PIN_CS   1
#define PIN_SCK  2
#define PIN_MOSI 3

GpioInit gpio(io);

static inline void cs_select()
{
//    asm volatile("nop \n nop \n nop");
	gpio_put(PIN_CS, 0);  // Active low
//    asm volatile("nop \n nop \n nop");
}

static inline void cs_deselect()
{
//    asm volatile("nop \n nop \n nop");
	gpio_put(PIN_CS, 1);
//    asm volatile("nop \n nop \n nop");
}

int main()
{
	stdio_usb_init();
	gpio.init();
//	uart_init(uart0, 57600);

	LedBlink blink(PICO_DEFAULT_LED_PIN, 100);
	while (! stdio_usb_connected())
	{
		blink.poll();
	}
	blink.setTime(300);
	Debug::showSysInfo(version);
	spi_init(spi0, 100*1000);
	gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
	gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
	gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
	gpio_set_function(PIN_CS, GPIO_FUNC_SPI);
	spi_set_format(spi0, 16, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);
//	gpio_init(PIN_CS);
//	gpio_set_dir(PIN_CS, GPIO_OUT);
//	gpio_put(PIN_CS, 1);

	gpio.showGpio();
	while (1)
	{
		blink.poll();
		uif();
	}
}

static void uif()
{
	uint8_t data[] = { 0x55, 0xa5, 1, 17, 25 };
	uint16_t data16[] = { 0x55ab }; //, 0xa5, 1, 17, 25 };
	int c = getchar_timeout_us(0);
	if (c < 0)
		return;
	switch (c)
	{
	case '.':
		Debug::showSysInfo(version);
		gpio.showGpio();
		break;
	case 's':
		printf("%s out %02x\n", __PRETTY_FUNCTION__, data[0]);
//		cs_select();
		spi_write_blocking(spi0, data, count_of(data));
//		cs_deselect();
		break;
	default:
		printf("rx=%04x\n", c);
		break;
	}
}
