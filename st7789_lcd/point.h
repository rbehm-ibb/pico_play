// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/29/2022 by behm
// ******************************************************

#ifndef POINT_H
#define POINT_H

#include <iostream>
#include "pico/stdlib.h"

class Point
{
	friend std::ostream &operator<<(std::ostream &s, const Point &p);
public:
	Point() : m_x(0), m_y(0) {}
	Point(uint16_t x, uint16_t y) : m_x(x), m_y(y) {}
	Point(const Point & rhs) : m_x(rhs.m_x), m_y(rhs.m_y) {}
	Point &operator=(const Point & rhs) { m_x = rhs.m_x; m_y = rhs.m_y; return *this; }
	bool operator==(const Point & rhs) const { return m_x == rhs.m_x && m_y == rhs.m_y; }
	bool operator!=(const Point & rhs) const { return ! operator==(rhs); }
	uint16_t x() const { return m_x; }
	uint16_t y() const { return m_y; }
	void setX(uint16_t newX) { m_x = newX; }
	void setY(uint16_t newY) { m_y = newY; }

protected:
	uint16_t m_x;
	uint16_t m_y;

};

class Size
{
	friend std::ostream &operator<<(std::ostream &s, const Size &p);
public:
	Size() : m_w(0), m_h(0) {}
	Size(uint16_t w, uint16_t h) : m_w(w), m_h(h) {}
	Size(const Size &s) : m_w(s.m_w), m_h(s.m_h) {}
	Size &operator=(const Size &s) { m_w = s.m_w; m_h = s.m_h; return *this; }
	bool operator==(const Size &s) const { return (m_w == s.m_w) && (m_h == s.m_h); }
	bool operator!=(const Size &s) const { return ! operator==(s); }
	uint16_t w() const { return m_w; }
	uint16_t h() const { return m_h; }
	void setW(uint16_t newW) { m_w = newW; }
	void setH(uint16_t newH) { m_h = newH; }
	uint area() const { return m_w * m_h; }

private:
	uint16_t m_w;
	uint16_t m_h;
};

class Rect
{
	friend std::ostream &operator<<(std::ostream &s, const Rect &r);
public:
	Rect() {}
	Rect(const Rect &r) : m_tl(r.m_tl), m_sz(r.m_sz) {}
	Rect(const Point &tl, const Size &sz) : m_tl(tl), m_sz(sz) {}
	Rect(const Point &tl, const Point &br) : m_tl(tl) { setBr(br); }
	Rect &operator=(const Rect &r) { m_tl = r.m_tl; m_sz = r.m_sz; return *this; }
	bool operator==(const Rect &r) const { return (m_tl == r.m_tl) && (m_sz == r.m_sz); }
	bool operator!=(const Rect &r) const { return ! operator==(r); }
	Point tl() const { return m_tl; }
	void setTl(Point newTl) { m_tl = newTl; }
	void setBr(Point newBr) { m_sz.setW(newBr.x() - left() + 1); m_sz.setH(newBr.y() - top() + 1); }
	Size sz() const { return m_sz; }
	void setSz(const Size &newSz) { m_sz = newSz; }
	uint16_t left() const { return m_tl.x(); }
	uint16_t right() const { return m_tl.x() + m_sz.w() - 1; }
	uint16_t top() const { return m_tl.y(); }
	uint16_t bottom() const { return m_tl.y() + m_sz.h() - 1; }
	Point br() const { return Point(left(), bottom()); }
	uint area() const { return m_sz.area(); }

protected:
	Point m_tl;
	Size m_sz;
};



#endif // POINT_H
