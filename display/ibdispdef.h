// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/24/2023 by behm
// ******************************************************

#ifndef IBDISPDEF_H
#define IBDISPDEF_H

#include <stdint.h>

typedef int16_t coord_t;

inline coord_t cmax(coord_t x1, coord_t x2) { return x1 > x2 ? x1 : x2; }
inline coord_t cmin(coord_t x1, coord_t x2) { return x1 < x2 ? x1 : x2; }

#endif // IBDISPDEF_H
