// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 10/31/2022 by behm
// ******************************************************

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "hardware/uart.h"
#include "pico/multicore.h"

const uint LED_PIN = 25;

static void out(int n);

void core1_entry()
{
	for (int i = 2; i < 8; ++i)
	{
		gpio_init(i);
		gpio_set_dir(i, GPIO_OUT);
	}
	int n = 0;
	while (1)
	{
		++n;
		out(n);
		sleep_ms(2);
	}
}


int main()
{

	bi_decl(bi_program_description("This is a test binary."));

	bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

	stdio_init_all();
	uart_init(uart0, 57600);

	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	 multicore_launch_core1(core1_entry);
	int n = 0;
	while (1)
	{
		gpio_put(LED_PIN, 0);
		++n;
//		out(n);
		sleep_ms(50);
		gpio_put(LED_PIN, 1);
		printf("Hello World 02: %d\n", n);
		sleep_ms(100);
	}
}

static void out(int n)
{
	for (int i = 0; i < 6; ++i)
	{
	(i+2, !!(n & (1 << i)));
	}
}
