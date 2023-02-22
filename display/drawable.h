// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/22/2023 by behm
// ******************************************************

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "ibdispdef.h"
#include "ibsize.h"
#include "ibpoint.h"
#include "ibrect.h"

struct Font
{
	uint16_t pixc;
	uint8_t w, h, bpc;
	char first;
	uint8_t font[];
};

class Drawable
{
public:
	Drawable(const IbSize &size);
	virtual void init(const IbSize &size) =  0;
	IbSize size() const { return m_size; }
	void setSize(const IbSize &newSize) { m_size = newSize; }

	color_t bg() const { return m_bg; }
	void setBg(color_t newBg) { m_bg = newBg; }

	Font *font() const { return m_font; }
	void setFont(Font *newFont) { m_font = newFont; }

	// drawing fcts
	virtual void drawPoint(const IbPoint p) = 0;
	virtual void drawRect(const IbRect &r);
	virtual void fillRect(const IbRect &r) = 0;
	virtual void drawHLine(const IbPoint p, coord_t w);
	virtual void drawVLine(const IbPoint p, coord_t h);
	virtual IbPoint drawChar(const IbPoint p, char c) = 0;

protected:
	IbSize m_size;
	Font *m_font;
	color_t m_bg;
	color_t m_fg;
};

#endif // DRAWABLE_H
