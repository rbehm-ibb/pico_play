// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/9/2023 by behm
// ******************************************************

#include <iostream>
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
	xx = false;
	bool rc = add_repeating_timer_ms(1000, &timer_callback, this, &timer);
	Timer *self = static_cast<Timer*>(timer.user_data);
	std::cout << __PRETTY_FUNCTION__ << m_id << " p" << timer.pool << " A" << timer.alarm_id << " =" << (self == this) << std::endl;
	return rc;
}

bool Timer::stop()
{
	return cancel_repeating_timer(&timer);
}

bool Timer::timer_callback(repeating_timer_t *rt)
{
	Timer *self = static_cast<Timer*>(rt->user_data);
	if (self)
	{
		self->xx = true;
		return ((++self->m_tick) < 50);
	}
	return false;
}
