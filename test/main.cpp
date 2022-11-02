// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 10/31/2022 by behm
// ******************************************************

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
//#include "pico/binary_info.h"
#include "hardware/uart.h"
#include "pico/multicore.h"

#include "core1.h"

//const uint LED_PIN = 25;
enum { LED_PIN = 25, CS = 1, SCLK, MOSI };
static int rx();
static void uif();
static void spiTx(uint16_t d);

int main()
{

//	stdio_init_all();
	stdio_usb_init();
//	uart_init(uart0, 57600);

	gpio_init(CS);
	gpio_set_dir(CS, GPIO_OUT);
	gpio_put(CS, 1);

	gpio_init(SCLK);
	gpio_set_dir(SCLK, GPIO_OUT);
	gpio_init(MOSI);
	gpio_set_dir(MOSI, GPIO_OUT);

	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	core1::start();
	int n = 0;
	while (1)
	{
		gpio_put(LED_PIN, 0);
		++n;
		sleep_ms(100);
		gpio_put(LED_PIN, 1);
//		printf("multi: %d\n", n);
		sleep_ms(200);
		uint32_t ts = time_us_32();
		uif();
		uint32_t te = time_us_32();
//		printf("dt=%u\n", te-ts);
	}
}

static void uif()
{
	int c = rx();
	if (c < 0)
		return;
	printf("rx=%04x\n", c);
	switch (c)
	{
	case 't':
		printf("spiTx\n");
		sleep_ms(100);
		spiTx(0x45aa);
	}
}

static void spiTx(uint16_t d)
{
	gpio_put(SCLK, 0);
	gpio_put(CS, 0);
	for (int i =  0; i <  16; ++i)
	{
//		busy_wait_us_32(1);
		gpio_put(MOSI, !!(d & 0x8000));
		gpio_put(SCLK, 1);
		d <<= 1;
//		busy_wait_us_32(1);
		gpio_put(SCLK, 0);
	}
	busy_wait_us_32(1);
	gpio_put(CS, 1);
}

static int rx()
{
	const int c = getchar_timeout_us(0);
//	if (c != PICO_ERROR_TIMEOUT)
//	{
//		printf("rx=%04x", c);
//	}
	return c;
}
