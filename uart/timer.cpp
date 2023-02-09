// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/9/2023 by behm
// ******************************************************

#include <iostream>
#include "hardware/gpio.h"
#include "timer.h"

int Timer::tid = 0;

Timer::Timer()
	: m_id(++tid)
	, m_tick(0)
{
}

bool Timer::start()
{
	m_tick = 0;
	m_hasTick = false;
	bool rc = add_repeating_timer_ms(-1000, &timer_callback, this, &timer);
	Timer *self = static_cast<Timer *>(timer.user_data);
	std::cout << __PRETTY_FUNCTION__ << m_id << " pool:" << timer.pool << " Alarm:" << timer.alarm_id << " =" << (self == this) << std::endl;
	return rc;
}

bool Timer::stop()
{
	return cancel_repeating_timer(&timer);
}

bool Timer::hasTick()
{
	bool has = m_hasTick;
	m_hasTick = false;
	return has;
}

bool Timer::timer_callback(repeating_timer_t *rt)
{
	static uint32_t mask = 1U << 26;
	Timer *self = static_cast<Timer *>(rt->user_data);
	if (self)
	{
		gpio_xor_mask(mask);
		self->m_hasTick = true;
		return ((++self->m_tick) < 50);
	}
	return false;
}
