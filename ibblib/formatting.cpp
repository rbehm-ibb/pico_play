// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 5/27/2023 by behm
// ******************************************************

#include <stdio.h>
#include "formatting.h"
#include <string.h>

namespace Formatting
{

const char *bin(uint16_t d, int ndig)
{
	static char s[20];
	memset(s, 0, sizeof(s));
	uint16_t mask = 1U << (ndig - 1);
	for (char *p = s; mask; ++p, mask >>= 1)
	{
		*p = (d & mask) ? '1' : '0';
	}
	return s;
}

const char *nbytesX(const uint8_t *d, int n)
{
	static char s[100];
	memset(s, 0, sizeof(s));
	for (int i = 0; i < n; ++i)
	{
		sprintf(s+3*i, "%02x ", d[i]);
	}
	return s;
}

}
