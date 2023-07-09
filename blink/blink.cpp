// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 6/2/2023 by behm
// ******************************************************

#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include "blink.h"


Blink::Blink(int pin)
	: Task(xname(pin), 100)
	, m_pin(pin)
{
	int core = pin & 0x01;
	m_AffinityMask = 1 << core;
//	setCoreAffinity(1 << core);
	printf("%s %s %x %x %d\n", __PRETTY_FUNCTION__, m_name, core, m_AffinityMask, m_pin);
}

void Blink::proc()
{
	puts(name());
	gpio_init(m_pin);
	gpio_set_dir(m_pin, GPIO_OUT);
	for (;;)
	{
		gpio_put(m_pin, 1);
		vTaskDelay(m_pin*100);
		gpio_put(m_pin, 0);
		vTaskDelay((8-m_pin)*100);
	}
}

char *Blink::xname(int pin)
{
//	static char s[15];
	sprintf(m_name, "Blink%d", pin);
	return m_name;
}

const char *Blink::name() const
{
	static char s[30];
	sprintf(s, "Blink%d %s %x core=%d", m_pin, m_name, m_AffinityMask, get_core_num());
	return s;
}
