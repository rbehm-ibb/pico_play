// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/24/2023 by behm
// ******************************************************

#ifndef RECT_H
#define RECT_H

#include <iostream>
#include "ibdispdef.h"
#include "point.h"
#include "size.h"

class IbRect
{
public:
	IbRect() {}	// internal _ct_ will do it
	IbRect(const IbRect &r) : m_tl(r.m_tl), m_br(r.m_br) { }
	IbRect(const IbPoint &tl, const IbPoint &br) : m_tl(tl), m_br(br) {}
	IbRect(const IbPoint &tl, const IbSize &sz) : m_tl(tl) , m_br(tl.x() + sz.w() - 1, tl.y() + sz.h() - 1) { }
	IbRect &operator=(const IbRect &r) { m_tl = r.m_tl; m_br = r.m_br; return *this; }
	IbPoint tl() const { return m_tl; }
	IbPoint br() const { return m_br; }
	void setTl(const IbPoint &newTl) { m_tl = newTl; }
	void setBr(const IbPoint &newBr) { m_br = newBr; }
	void moveBy(const IbPoint &p) { m_tl += p; m_br += p; }
	IbSize size() const { return IbSize(m_br.x() - m_tl.x() + 1, m_br.y() - m_tl.y() + 1); }
	coord_t w() const { return size().w(); }
	coord_t h() const { return size().h(); }
	coord_t left() const { return m_tl.x(); }
	coord_t right() const { return m_br.x(); }
	coord_t top() const { return m_tl.y(); }
	coord_t bottom() const { return m_br.x(); }
	bool isNull() const { return m_tl == m_br; }
	bool operator==(const IbRect &p) const { return m_tl == p.m_tl && m_br == p.m_br; }
	bool operator!=(const IbRect &p) const { return !(*this == p); }
	friend std::ostream &operator<<(std::ostream &s, const IbRect &r);

protected:
	IbPoint m_tl;
	IbPoint m_br;
};

#endif // RECT_H
