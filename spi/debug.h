// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/7/2022 by behm
// ******************************************************

#ifndef DEBUG_H
#define DEBUG_H

#include "pico/stdlib.h"

class Debug
{
public:
	Debug();
	static void dump(const void *src, size_t size, const char *title = nullptr);
	static void showIos();
	static void showSysInfo(const char *version);
private:
	static const char *gpioConf(int n);
};

#endif // DEBUG_H
