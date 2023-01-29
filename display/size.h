// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/24/2023 by behm
// ******************************************************

#ifndef SIZE_H
#define SIZE_H

#include <iostream>
#include "ibdispdef.h"

class IbSize
{
public:
	IbSize() : m_w(0), m_h(0) {}
	IbSize(const IbSize &s) : m_w(s.m_w), m_h(s.m_h) { }
	IbSize(coord_t w, coord_t h) : m_w(w), m_h(h) {}
	coord_t w() const { return m_w; }
	coord_t h() const { return m_h; }
	void setW(coord_t newW) { m_w = newW; }
	void setH(coord_t newH) { m_h = newH; }
	bool isNull() { return m_w == 0 && m_h == 0; }
	bool operator==(const IbSize &p) const { return m_w == p.m_w && m_h == p.m_h; }
	bool operator!=(const IbSize &p) const { return !(*this == p); }
	IbSize &operator+=(const IbSize &p) { m_w += p.m_w; m_h += p.m_h; return *this; }
	IbSize &operator+=(const coord_t delta) { m_w += delta; m_h += delta; return *this; }
	friend inline IbSize operator+(const IbSize &p1, const IbSize &p2);
	friend std::ostream &operator<<(std::ostream &s, const IbSize &sz);

protected:
	coord_t m_w;
	coord_t m_h;
};

inline IbSize operator+(const IbSize &p1, const IbSize &p2) { return IbSize(p1.m_w + p2.m_w, p1.m_h + p2.m_h); }

#endif // SIZE_H
