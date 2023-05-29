// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 5/27/2023 by behm
// ******************************************************

#ifndef FORMATTING_H
#define FORMATTING_H

#include <iostream>

namespace Formatting
{
const char *bin(uint16_t d, int ndig);
const char *nbytesX(const uint8_t *d, int n);
};

#endif // FORMATTING_H
