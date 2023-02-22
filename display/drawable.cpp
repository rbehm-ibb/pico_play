// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/22/2023 by behm
// ******************************************************

#include "drawable.h"

Drawable::Drawable(const IbSize &size)
	: m_size(size)
	, m_font(nullptr)
	, m_bg(rgb565(0, 0, 0))
	, m_fg(rgb565(255, 255, 255))
{
}

void Drawable::drawRect(const IbRect &r)
{
	const int w = r.w();
	const int h = r.h();
	drawHLine(r.tl(), w);
	drawHLine(r.bl(), w);
	drawVLine(r.tl(), h);
	drawVLine(r.tr(), h);
}











