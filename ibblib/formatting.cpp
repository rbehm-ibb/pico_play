// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 5/27/2023 by behm
// ******************************************************

#include <stdio.h>
#include "formatting.h"
#include <string.h>

namespace Frm
{

static char tchar[100];

static void clear()
{
	memset(tchar, 0, sizeof(tchar));
}

const char *bin(uint16_t d, int ndig)
{
	clear();
	uint16_t mask = 1U << (ndig - 1);
	for (char *p = tchar; mask; ++p, mask >>= 1)
	{
		*p = (d & mask) ? '1' : '0';
	}
	return tchar;
}

const char *hex(uint32_t d, int ndig)
{
	clear();
	sprintf(tchar, "%0*x", ndig, d);
	return tchar;
}

#if 0
const char *nbytesX(const uint8_t *d, int n)
{
	clear();
	for (int i = 0; i < n; ++i)
	{
		sprintf(tchar+3*i, "%02x ", d[i]);
	}
	return tchar;
}

const char *nbytesX(const std::vector<uint8_t> d, int from, int n)
{
	clear();
	if (n < 0)
	{
		n = d.size();
	}
	if (from + n > d.size())
	{
		n = d.size() - from;
	}
	static char s[100];
	for (int i = 0; i < n; ++i)
	{
		sprintf(tchar+3*i, "%02x ", d[from+i]);
	}
	return tchar;
}
#endif
}

