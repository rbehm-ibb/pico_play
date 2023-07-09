// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 6/28/2023 by behm
// ******************************************************

#include <string.h>
#include "flashlog.h"
#include <pico/time.h>

FlashLog::FlashLog()
	: bufPtr(buffer)
	, flashPtr(flashbase)
{
	memset(buffer, 0, sizeof(buffer));

}

void FlashLog::append(const char *s)
{
	m_lastTime = get_absolute_time();
}

void FlashLog::poll()
{

}
