// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/9/2023 by behm
// ******************************************************

#ifndef TIMER_H
#define TIMER_H

#include "pico/stdlib.h"

class Timer
{
public:
	Timer();
	bool start();
	bool stop();
	int id() const { return m_id; }
	int tick() const { return m_tick; }
	bool xxx() { bool x = xx; xx = false; return x;}
private:
	const int m_id;
	static int tid;
	repeating_timer_t timer;
	int m_tick;
	bool xx;
	static bool timer_callback(repeating_timer_t *rt);
};

#endif // TIMER_H
