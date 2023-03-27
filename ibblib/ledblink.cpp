// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/10/2022 by behm
// ******************************************************

#include "pico/time.h"
#include "hardware/gpio.h"
#include "ledblink.h"

LedBlink::LedBlink(uint pin, uint ms)
	: m_pinMask(1U << pin)
	, m_ms(ms)
{
	gpio_init(pin);
	gpio_set_dir(pin, GPIO_OUT);
	gpio_put(pin, 1);
	m_time = delayed_by_ms(get_absolute_time(), m_ms);
}

void LedBlink::poll()
{
	absolute_time_t t = get_absolute_time();
	if (t > m_time)
	{
		m_time = delayed_by_ms(t, m_ms);
		gpio_xor_mask(m_pinMask);
	}
}

void LedBlink::setTime(absolute_time_t t)
{
	m_ms = t;
	m_time = make_timeout_time_ms(m_ms);
}

void LedBlink::toggle()
{
	gpio_xor_mask(m_pinMask);
}
