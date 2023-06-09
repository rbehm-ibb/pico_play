// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 5/27/2023 by behm
// ******************************************************

#ifndef FORMATTING_H
#define FORMATTING_H

#include <stdint.h>
#include <vector>


namespace Frm
{
const char *bin(uint16_t d, int ndig);
const char *hex(uint32_t d, int ndig);
//const char *nbytesX(const uint8_t *d, int n);
//const char *nbytesX(const std::vector<uint8_t> d, int from = 0, int n=-1);

};

#endif // FORMATTING_H
