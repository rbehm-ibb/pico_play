// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 6/28/2023 by behm
// ******************************************************

#ifndef FLASHLOG_H
#define FLASHLOG_H

#include <stdio.h>
#include <hardware/flash.h>
#include <hardware/sync.h>


class FlashLog
{
public:
	FlashLog();
	void append(const char *s);
	void  poll();
private:
	char buffer[FLASH_PAGE_SIZE];
	char *bufPtr;
	uint32_t flashPtr;
	void flush();
	absolute_time_t m_lastTime;
	static constexpr uint32_t flashbase = 4L*1024*1024+0x4000;	//past keys
};

#endif // FLASHLOG_H
