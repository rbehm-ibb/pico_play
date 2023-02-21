// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/24/2023 by behm
// ******************************************************

#ifndef DISPLAYBASE_H
#define DISPLAYBASE_H

#include "spibase.h"
#include "ibsize.h"
#include "ibpoint.h"
#include "ibrect.h"

class DisplayBase
{
public:
	DisplayBase(SpiBase * const ioChannel, const IbSize &size);
	virtual void init() = 0;
	IbSize size() const { return m_size; }

	IbRect rect() const { return m_rect; }
	IbRect dispRect() const { return IbRect(IbPoint(0, 0), m_size); }
	virtual void setRect(const IbRect &newRect) = 0;

protected:
	SpiBase * const m_ioChannel;	/// the hw channel to talk to the display
	const IbSize m_size;	/// the size of the display
	IbRect m_rect;		/// the current drawing rect
};

#endif // DISPLAYBASE_H
