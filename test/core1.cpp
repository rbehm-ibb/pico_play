// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 11/1/2022 by behm
// ******************************************************

#include "hardware/gpio.h"
#include "pico/multicore.h"
#include "core1.h"

const int offset = 4;	// first used pin

core1::core1()
{
}

void core1::start()
{
	multicore_reset_core1();
	multicore_launch_core1(core1::run);
}

void core1::out(int n)
{
	for (int i = 0; i < 6; ++i)
	{
		gpio_put(i + offset, !!(n & (1 << i)));
	}
}

void core1::run()
{
	for (int i = offset; i < 8; ++i)
	{
		gpio_init(i);
		gpio_set_dir(i, GPIO_OUT);
	}
	printf("core1 start\n");
	int n = 0;
	while (1)
	{
		++n;
		out(n);
		busy_wait_us_32(1000*1);
//		if (n > 5000)
//		{
//			printf("core1 ---\n");
//			n = 0;
//		}
	}
}
