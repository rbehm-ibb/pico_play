// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/10/2022 by behm
// ******************************************************

#ifndef LEDBLINK_H
#define LEDBLINK_H

#include "pico/types.h"

class LedBlink
{
public:
	LedBlink(uint pin, uint ms);
	void poll();
	void setTime(absolute_time_t t);
	void toggle();
private:
	const uint32_t m_pinMask;
	uint m_ms;
	absolute_time_t m_time;
};

#endif // LEDBLINK_H
