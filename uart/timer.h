// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/9/2023 by behm
// ******************************************************

#ifndef TIMER_H
#define TIMER_H

#include "pico/time.h"

class Timer
{
public:
	Timer();
	bool start();
	bool stop();
	int id() const { return m_id; }
	int tick() const { return m_tick; }
	bool hasTick();
private:
	const int m_id;
	static int tid;
	repeating_timer_t timer;
	volatile int m_tick;
	volatile bool m_hasTick;
	static bool timer_callback(repeating_timer_t *rt);
};

#endif // TIMER_H
