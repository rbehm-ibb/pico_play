// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/29/2022 by behm
// ******************************************************

#ifndef POINT_H
#define POINT_H

#include <iostream>

typedef int16_t coord_t;

inline coord_t min(coord_t x1, coord_t x2) { return x1 < x2 ?  x1 : x2; }
inline coord_t max(coord_t x1, coord_t x2) { return x1 > x2 ?  x1 : x2; }

class Point
{
	friend std::ostream &operator<<(std::ostream &s, const Point &p);
public:
	Point() : m_x(0), m_y(0) {}
	Point(coord_t x, coord_t y) : m_x(x), m_y(y) {}
	Point(const Point & rhs) : m_x(rhs.m_x), m_y(rhs.m_y) {}
	Point &operator=(const Point & rhs) { m_x = rhs.m_x; m_y = rhs.m_y; return *this; }
	friend inline Point operator+(const Point &p1, const Point &p2);
	inline bool operator==(const Point & rhs) const { return m_x == rhs.m_x && m_y == rhs.m_y; }
	inline bool operator!=(const Point & rhs) const { return ! operator==(rhs); }
	coord_t x() const { return m_x; }
	coord_t y() const { return m_y; }
	void setX(coord_t newX) { m_x = newX; }
	void setY(coord_t newY) { m_y = newY; }
	inline Point &operator+=(const Point & rhs) { m_x += rhs.m_x; m_y += rhs.m_y; return *this; }

protected:
	coord_t m_x;
	coord_t m_y;

};

class Size
{
	friend std::ostream &operator<<(std::ostream &s, const Size &p);
public:
	Size() : m_w(0), m_h(0) {}
	Size(coord_t w, coord_t h) : m_w(w), m_h(h) {}
	Size(const Size &s) : m_w(s.m_w), m_h(s.m_h) {}
	Size &operator=(const Size &s) { m_w = s.m_w; m_h = s.m_h; return *this; }
	inline bool operator==(const Size &s) const { return (m_w == s.m_w) && (m_h == s.m_h); }
	inline bool operator!=(const Size &s) const { return ! operator==(s); }
	Size &operator+=(const Size &s) { m_w += s.m_w; m_h += s.m_h; return *this; }
	coord_t w() const { return m_w; }
	coord_t h() const { return m_h; }
	void setW(coord_t newW) { m_w = newW; }
	void setH(coord_t newH) { m_h = newH; }
	int area() const { return m_w * m_h; }

private:
	coord_t m_w;
	coord_t m_h;
};

class Rect
{
	friend std::ostream &operator<<(std::ostream &s, const Rect &r);
public:
	Rect() : x1(0), x2(0), y1(0), y2(0) {}
	Rect(const Rect &r) : x1(r.x1), x2(r.x2), y1(r.y1), y2(r.y2) {}
	Rect(coord_t x, coord_t y, coord_t w, coord_t h) : x1(x), x2(x+w-1), y1(y), y2(y+h-1) {}
	Rect(const Point &tl, const Size &sz) { setTl(tl); setSz(sz); }
	Rect(const Point &tl, const Point &br) { setTl(tl); setBr(br); }
	inline Rect &operator=(const Rect &r) { x1 = r.x1; x2 =  r.x2; y1 = r.y1; y2 = r.y2; return *this; }
	inline bool operator==(const Rect &r) const { return (x1 == r.x1) && (x2 == r.x2) && (y1 == r.y1) && (y2  == r.y2); }
	inline bool operator!=(const Rect &r) const { return ! operator==(r); }
	inline bool empty() const { return (x1==x2) || (y1==y2); }
	inline bool valid() const { return (x1 <= x2) && (y1 <= y2); }
	inline Point tl() const { return Point(x1, y1); }
	inline Point br() const { return Point(x2, y2); }
	inline Point tr() const { return Point(x2, y1); }
	inline Point bl() const { return Point(x1, y2); }
	inline void setTl(Point newTl) { x1 = newTl.x(); y1 = newTl.y(); }
	inline void setBr(Point newBr) { x2 = newBr.x(); y2 = newBr.y(); }
	inline Size sz() const { return Size(width(), height()); }
	inline void setSz(const Size &newSz) { x2 =  x1  + newSz.w() - 1; y2 =  y1 +  newSz.h() - 1; }
	coord_t left() const { return x1; }
	coord_t right() const { return x2; }
	coord_t top() const { return y1; }
	coord_t bottom() const { return y2; }
	coord_t width() const { return x2 - x1 + 1; }
	coord_t height() const { return y2 - y1 + 1; }
	uint area() const { return width() *height(); }
	inline Rect normalized() const { return Rect(Point(min(x1, x2), min(y1, y2)), Point(max(x1, x2), max(y1, y2))); }
	inline Rect &normalize() { *this  =  normalized(); return *this; }
	Rect & operator|=(const Point &p)  { x1 -= p.x(); y1 -= p.y(); x2 += p.x(); y2 += p.y(); return *this; }
	friend Rect operator|(const Rect &r, const Point &p);
	inline Rect &operator+=(const Size &s) { x2 += s.w(); y2 += s.h(); return *this; }
	inline Rect &operator+=(const Point &p) { x1 += p.x(); x2 +=  p.x(); y1 += p.y(); y2 += p.y();return *this; }
	inline Rect &operator|=(int n) { x1 -= n; x2 +=  n; y1 -= n; y2 += n;return *this; }

protected:
	coord_t x1;
	coord_t x2;
	coord_t y1;
	coord_t y2;
};

inline Point operator+(const Point &p1, const Point &p2)
{
	return Point(p1.x() + p2.x(), p1.y() + p2.y());
}

inline Rect operator|(const Rect &r, const Point &p)
{
	class Rect rr;
	rr.x1 = r.x1 - p.x();
	rr.y1 = r.y1 - p.y();
	rr.x2 = r.y1 + p.x();
	rr.y2 =  r.y2 + p.y();
	return rr;
}


#endif // POINT_H
