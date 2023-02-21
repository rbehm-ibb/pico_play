// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/24/2023 by behm
// ******************************************************

#ifndef POINT_H
#define POINT_H

#include <iostream>
#include "ibdispdef.h"


/// Point represents a point in display coordinates
class IbPoint
{
public:
	/// \brief Point, empty _ct_
	/// creates a Point initialized to 0
	IbPoint() : m_x(0), m_y(0) {}
	/// \brief Point creates a point from coords
	/// \param x
	/// \param y
	IbPoint(coord_t x, coord_t y) : m_x(x), m_y(y) {}
	/// \brief Point copy _ct_
	/// \param p the source to copy
	IbPoint(const IbPoint &p) : m_x(p.m_x), m_y(p.m_y) {}
	IbPoint &operator=(const IbPoint &p) { m_x = p.m_x; m_y = p.m_y; return *this; }
	constexpr coord_t x() const { return m_x; }
	constexpr coord_t y() const { return m_y; }
	void setX(coord_t newX) { m_x = newX; }
	void setY(coord_t newY) { m_y = newY; }
	bool isNull() { return m_x == 0 && m_y == 0; }
	bool operator==(const IbPoint &p) const { return m_x == p.m_x && m_y == p.m_y; }
	bool operator!=(const IbPoint &p) const { return !(*this == p); }
	IbPoint &operator+=(const IbPoint &p) { m_x += p.m_x; m_y += p.m_y; return *this; }
	friend inline IbPoint operator+(const IbPoint &p1, const IbPoint &p2);
	friend std::ostream &operator<<(std::ostream &s, const IbPoint &p);
protected:
	coord_t m_x;
	coord_t m_y;
};

inline IbPoint operator+(const IbPoint &p1, const IbPoint &p2) { return IbPoint(p1.m_x + p2.m_x, p1.m_y + p2.m_y); }

#endif // POINT_H
