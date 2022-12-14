// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/10/2022 by behm
// ******************************************************

#ifndef LEDBLINK_H
#define LEDBLINK_H

#include "pico/time.h"

class LedBlink
{
public:
	LedBlink(uint pin, uint ms);
	void poll();
private:
	const uint m_pin;
	const uint m_ms;
	absolute_time_t m_time;
	bool m_on;
};

#endif // LEDBLINK_H
