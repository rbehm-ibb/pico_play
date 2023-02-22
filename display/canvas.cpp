// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/22/2023 by behm
// ******************************************************

#include "canvas.h"

Canvas::Canvas(const IbSize &size)
	: Drawable(size)
	, m_buffer(nullptr)
{
}

Canvas::~Canvas()
{
	delete m_buffer;
}

void Canvas::drawPoint(const IbPoint p)
{
}

void Canvas::fillRect(const IbRect &r)
{
}

void Canvas::drawHLine(const IbPoint p, coord_t w)
{
}

void Canvas::drawVLine(const IbPoint p, coord_t h)
{
}

IbPoint Canvas::drawChar(const IbPoint p, char c)
{
	return p;
}
