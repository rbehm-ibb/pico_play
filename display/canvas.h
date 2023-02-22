// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/22/2023 by behm
// ******************************************************

#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include "ibdispdef.h"
#include "ibsize.h"
#include "ibpoint.h"
#include "ibrect.h"
#include "drawable.h"

class Canvas : public Drawable
{
public:
	Canvas(const IbSize &size);
	virtual ~Canvas();
//	void init(const IbSize &size) override;
	void drawPoint(const IbPoint p) override;
	void fillRect(const IbRect &r) override;
	void drawHLine(const IbPoint p, coord_t w) override;
	void drawVLine(const IbPoint p, coord_t h) override;
	IbPoint drawChar(const IbPoint p, char c) override;
protected:
	uint8_t *m_buffer;
	std::vector<color_t> m_palette;
};

class Canvas1 : public Canvas
{
public:
	Canvas1(const IbSize &size);
	virtual ~Canvas1();
};

#endif // CANVAS_H
