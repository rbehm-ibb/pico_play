#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
//#include "tusb.h"

const uint LED_PIN = 25;

static void out(int n);

int main()
{

	bi_decl(bi_program_description("This is a test binary."));

	bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

	stdio_init_all();

	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	for (int i = 0; i < 8; ++i)
	{
		gpio_init(i);
		gpio_set_dir(i, GPIO_OUT);
	}
	int n = 0;
	while (1)
	{
//		gpio_put(LED_PIN, 0);
		++n;
		out(n);
//		sleep_ms(50);
//		gpio_put(LED_PIN, 1);
//		printf("Hello World 02: %d\n", n);
//		sleep_ms(100);
	}
}

static void out(int n)
{
	for (int i = 0; i < 8; ++i)
	{
		gpio_put(i, !!(n & (1 << i)));
	}
}
