// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 4/26/2023 by behm
// ******************************************************

#ifndef MONOFLOPTIMER_H
#define MONOFLOPTIMER_H

#include <pico/time.h>

class MonoFlopTimer
{
public:
	MonoFlopTimer(uint count);
	void start(uint n, uint32_t del) { if (n < m_count) { m_timer[n] = del; } }
	bool expired(uint n) { if (n < m_count) { return m_timer[n] == 0; } return false; }
	static constexpr uint tickPerMsec = 20;
private:
	repeating_timer_t m_rtimer;
	const uint m_count;
	uint32_t *m_timer;
	static bool callback(repeating_timer_t *rt);
};

#endif // MONOFLOPTIMER_H
