// ******************************************************
// * copyright (C) 2021 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 8/12/2021 by behm
// ******************************************************

#include "arddef.h"

void strcpyN(char *dest, const char * src, size_t max)
{
	strncpy(dest, src, max);
	dest[max-1] = '\0';
}
