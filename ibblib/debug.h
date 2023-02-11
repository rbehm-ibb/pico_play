// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/7/2022 by behm
// ******************************************************

#ifndef DEBUG_H
#define DEBUG_H

#include <vector>
#include "pico/stdlib.h"

class Debug
{
public:
//	Debug();
	static void dump(const void *src, size_t size, const char *title = nullptr);
	static void dump(const std::vector<uint8_t> &d, const char *title = nullptr);
	static void dump(const std::vector<uint16_t> &d, const char *title = nullptr);	// will dump with swapped bytes
	static void showSysInfo(const char *version);
private:
};

#endif // DEBUG_H
