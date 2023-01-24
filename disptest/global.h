// ******************************************************
// * copyright (C) 2021 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/22/2021 by behm
// ******************************************************

#ifndef GLOBAL_H
#define GLOBAL_H

#include "arddef.h"
#include <cstdint>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

typedef uint16_t color_t;
typedef int16_t coord_t;
inline coord_t min(const coord_t x1, const coord_t x2) { return x1 < x2 ? x1 : x2; }
inline coord_t max(const coord_t x1, const coord_t x2) { return x1 > x2 ? x1 : x2; }

#endif // GLOBAL_H
