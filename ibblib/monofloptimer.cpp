// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 4/26/2023 by behm
// ******************************************************

#include "monofloptimer.h"
#include <string.h>
#include <hardware/gpio.h>

constexpr uint32_t toggleMask = 1L << 2;

MonoFlopTimer::MonoFlopTimer(uint count)
	: m_count(count)
	, m_timer(new  uint32_t[count])
{
	memset(m_timer, 0, sizeof(*m_timer * m_count));
	add_repeating_timer_us(250/*1000 / tickPerMsec*/, &callback, this, &m_rtimer);
s}



bool MonoFlopTimer::callback(repeating_timer_t *rt)
{
	gpio_xor_mask(toggleMask);
	MonoFlopTimer *const me = static_cast<MonoFlopTimer *>(rt->user_data);
	if (me && me->m_timer)
	{
		for (uint i = 0; i < me->m_count; ++i)
		{
			if (me->m_timer[i])
			{
				--(me->m_timer[i]);
			}
		}
		return true;
	}
	return false;
}
