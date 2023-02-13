// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/24/2023 by behm
// ******************************************************

#include "rect.h"

//namespace IbDisp
//{

std::ostream &operator<<(std::ostream &s, const IbRect &r)
{
	return s << "R{" << r.tl() << "," << r.br() << "}";
}

IbRect &IbRect::operator+=(const coord_t x)
{
	m_tl += IbPoint(-x, -x);
	m_br += IbPoint(x, x);
	return *this;
}

bool IbRect::contains(const IbPoint &p)
{
	if (m_tl.x() > p.x())
		return false;	// left of
	if (m_br.x() < p.x())
		return false;	// right  of
	if (m_tl.y() > p.y())
		return false;	// above
	if (m_br.y() < p.y())
		return false;	// below
	return true;
}
