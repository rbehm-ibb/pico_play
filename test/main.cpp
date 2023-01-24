// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 10/31/2022 by behm
// ******************************************************

#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

//#include "core1.h"
#include "pio_spi.h"

//const uint LED_PIN = 25;
enum { LED_PIN = 25, CS = 1, SCLK, MOSI };
static int rx();
static void uif(const pio_spi_inst_t *spi);
static void spiTx(uint16_t d);
static void testPio();


#define PIN_SCK 1
#define PIN_MOSI 2
#define PIN_MISO 2 // same as MOSI, so we get loopback

#define BUF_SIZE 20

void test(const pio_spi_inst_t *spi) {
    static uint8_t txbuf[BUF_SIZE];
    static uint8_t rxbuf[BUF_SIZE];
    printf("TX:");
    for (int i = 0; i < BUF_SIZE; ++i) {
	txbuf[i] = rand() >> 16;
	rxbuf[i] = 0;
	printf(" %02x", (int) txbuf[i]);
    }
    printf("\n");

    pio_spi_write8_read8_blocking(spi, txbuf, rxbuf, BUF_SIZE);

    printf("RX:");
    bool mismatch = false;
    for (int i = 0; i < BUF_SIZE; ++i) {
	printf(" %02x", (int) rxbuf[i]);
	mismatch = mismatch || rxbuf[i] != txbuf[i];
    }
    if (mismatch)
	printf("\nNope\n");
    else
	printf("\nOK\n");
}

int main()
{

//	stdio_init_all();
	stdio_usb_init();
//	uart_init(uart0, 57600);

//	gpio_init(CS);
//	gpio_set_dir(CS, GPIO_OUT);
//	gpio_put(CS, 1);

//	gpio_init(SCLK);
//	gpio_set_dir(SCLK, GPIO_OUT);
//	gpio_init(MOSI);
//	gpio_set_dir(MOSI, GPIO_OUT);

	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	pio_spi_inst_t spi = {
		.pio = pio0,
		.sm = 0
	};
	float clkdiv = 15.635f;  // 1 MHz @ 125 clk_sys
	uint cpha0_prog_offs = pio_add_program(spi.pio, &spi_cpha0_program);
	uint cpha1_prog_offs = pio_add_program(spi.pio, &spi_cpha1_program);
	for (int cpha = 0; cpha <= 1; ++cpha) {
	     for (int cpol = 0; cpol <= 1; ++cpol) {
		 printf("CPHA = %d, CPOL = %d\n", cpha, cpol);
		 pio_spi_init(spi.pio, spi.sm,
			      cpha ? cpha1_prog_offs : cpha0_prog_offs,
			      8,       // 8 bits per SPI frame
			      clkdiv,
			      cpha,
			      cpol,
			      PIN_SCK,
			      PIN_MOSI,
			      PIN_MISO
		 );
		 test(&spi);
		 sleep_ms(10);
	     }
	 }

//	core1::start();
	int n = 0;
	while (1)
	{
		gpio_put(LED_PIN, 0);
		++n;
		sleep_ms(100);
		gpio_put(LED_PIN, 1);
		printf("Xmulti: %d\n", n);
		sleep_ms(200);
		uif(&spi);
	}
}

static void uif(const pio_spi_inst_t *spi)
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
	case 's':
		test(spi);
//		testPio();
		break;
	}
}

static void testPio()
{

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

#include "pio_spi.c"
