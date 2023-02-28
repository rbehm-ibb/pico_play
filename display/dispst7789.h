// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/27/2023 by behm
// ******************************************************

#ifndef DISPST7789_H
#define DISPST7789_H

#include "displaybase.h"

class DispSt7789 : public DisplayBase
{
public:
	DispSt7789(SpiBase * const ioChannel, const IbSize &size);

	// Drawable interface
public:
	virtual void drawPoint(const IbPoint p) override;
	virtual void fillRect(const IbRect &r) override;
	virtual void init() override;
	virtual void drawHLine(const IbPoint p, coord_t w) override;
	virtual void drawVLine(const IbPoint p, coord_t h) override;
	virtual IbPoint drawChar(const IbPoint p, char c) override;

protected:
	virtual void setRect(const IbRect &newRect) override;
};

#endif // DISPST7789_H
