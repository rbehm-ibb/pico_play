// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/24/2023 by behm
// ******************************************************

#ifndef DISPLAYBASE_H
#define DISPLAYBASE_H

#include "ibdispdef.h"
#include "spibase.h"
#include "ibsize.h"
#include "ibpoint.h"
#include "ibrect.h"
#include "drawable.h"

class DisplayBase : public Drawable
{
public:
	enum Rotation { Rot0, Rot90, Rot180, Rot270 };
	DisplayBase(SpiBase * const ioChannel, const IbSize &size);
	virtual void init() =  0;
	IbSize size() const { return m_size; }
	IbRect dispRect() const { return IbRect(IbPoint(0, 0), m_size); }

	Rotation rot() const { return m_rot; }
	void setRot(Rotation newRot);

protected:
	void sendInitSeq(const uint8_t *list);
	IbRect rect() const { return m_rect; }
	virtual void setRect(const IbRect &newRect) = 0;
	SpiBase * const m_ioChannel;	/// the hw channel to talk to the display
	Rotation m_rot;		/// the current display rotation
	IbRect m_rect;		/// the current drawing rect
};

#endif // DISPLAYBASE_H
