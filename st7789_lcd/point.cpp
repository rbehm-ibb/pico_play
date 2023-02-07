// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/29/2022 by behm
// ******************************************************

#include "point.h"

std::ostream &operator<<(std::ostream &s, const Point &p)
{
	return s << "(" << p.x() << "," << p.y() << ")";
}

std::ostream &operator<<(std::ostream &s, const Size &p)
{
	return s << "{" << p.w() << "," << p.h() << "}";
}

std::ostream &operator<<(std::ostream &s, const Rect &r)
{
	return s << "[" << r.tl() << "," << r.sz() << "]";
}