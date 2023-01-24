// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/10/2022 by behm
// ******************************************************

#include "ledblink.h"
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"

LedBlink::LedBlink(uint pin, uint ms)
	: m_pin(pin)
	, m_ms(ms)
	, m_on(true)
{
	gpio_init(m_pin);
	gpio_set_dir(m_pin, GPIO_OUT);
	gpio_put(m_pin, m_on);
	m_time = delayed_by_ms(get_absolute_time(), m_ms);
}

void LedBlink::poll()
{
	absolute_time_t t = get_absolute_time();
//	absolute_time_t dt = (t - m_time) / 1000;
	if (t > m_time)
	{
		m_time = delayed_by_ms(t, m_ms);
		gpio_put(m_pin, m_on);
		m_on = ! m_on;
	}
}

void LedBlink::setTime(absolute_time_t t)
{
	m_ms = t;
	m_time = delayed_by_ms(get_absolute_time(), m_ms);
}
