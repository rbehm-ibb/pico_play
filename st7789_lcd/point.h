// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/29/2022 by behm
// ******************************************************

#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
	friend std::ostream &operator<<(std::ostream &s, const Point &p);
public:
	Point() : m_x(0), m_y(0) {}
	Point(int x, int y) : m_x(x), m_y(y) {}
	Point(const Point & rhs) : m_x(rhs.m_x), m_y(rhs.m_y) {}
	Point &operator=(const Point & rhs) { m_x = rhs.m_x; m_y = rhs.m_y; return *this; }
	bool operator==(const Point & rhs) const { return m_x == rhs.m_x && m_y == rhs.m_y; }
	bool operator!=(const Point & rhs) const { return ! operator==(rhs); }
	int x() const { return m_x; }
	int y() const { return m_y; }
	void setX(int newX) { m_x = newX; }
	void setY(int newY) { m_y = newY; }
	Point &operator+=(const Point & rhs) { m_x += rhs.m_x; m_y += rhs.m_y; return *this; }

protected:
	int m_x;
	int m_y;

};

class Size
{
	friend std::ostream &operator<<(std::ostream &s, const Size &p);
public:
	Size() : m_w(0), m_h(0) {}
	Size(int w, int h) : m_w(w), m_h(h) {}
	Size(const Size &s) : m_w(s.m_w), m_h(s.m_h) {}
	Size &operator=(const Size &s) { m_w = s.m_w; m_h = s.m_h; return *this; }
	bool operator==(const Size &s) const { return (m_w == s.m_w) && (m_h == s.m_h); }
	bool operator!=(const Size &s) const { return ! operator==(s); }
	Size &operator+=(const Size &s) { m_w += s.m_w; m_h += s.m_h; return *this; }
	int w() const { return m_w; }
	int h() const { return m_h; }
	void setW(int newW) { m_w = newW; }
	void setH(int newH) { m_h = newH; }
	int area() const { return m_w * m_h; }

private:
	int m_w;
	int m_h;
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
	Rect &operator+=(const Size &s) { m_sz += s; return *this; }
	Rect &operator+=(const Point &p) { m_tl += p; return *this; }
	friend inline Point operator+(const Point &p1, const Point &p2);
	Point tl() const { return m_tl; }
	Point br() const { return Point(right(), bottom()); }
	Point tr() const { return Point(right(), top()); }
	Point bl() const { return Point(left(), bottom()); }
	void setTl(Point newTl) { m_tl = newTl; }
	void setBr(Point newBr) { m_sz.setW(newBr.x() - left() + 1); m_sz.setH(newBr.y() - top() + 1); }
	Size sz() const { return m_sz; }
	void setSz(const Size &newSz) { m_sz = newSz; }
	int left() const { return m_tl.x(); }
	int right() const { return m_tl.x() + m_sz.w() - 1; }
	int top() const { return m_tl.y(); }
	int bottom() const { return m_tl.y() + m_sz.h() - 1; }
	int width() const { return m_sz.w(); }
	int height() const { return m_sz.h(); }
	uint area() const { return m_sz.area(); }

protected:
	Point m_tl;
	Size m_sz;
};

inline Point operator+(const Point &p1, const Point &p2)
{
	return Point(p1.x() + p2.x(), p1.y() + p2.y());
}


#endif // POINT_H
