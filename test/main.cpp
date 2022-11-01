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

const uint LED_PIN = 25;

int main()
{

//	stdio_init_all();
	stdio_usb_init();
	uart_init(uart0, 57600);

	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	core1::start();
//	multicore_reset_core1();
//	multicore_launch_core1(core1::run);
	int n = 0;
	while (1)
	{
		gpio_put(LED_PIN, 0);
		++n;
		sleep_ms(100);
		gpio_put(LED_PIN, 1);
		printf("multi: %d\n", n);
		sleep_ms(200);
	}
}
