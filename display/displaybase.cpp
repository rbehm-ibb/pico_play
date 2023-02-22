// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/24/2023 by behm
// ******************************************************

#include "displaybase.h"

DisplayBase::DisplayBase(SpiBase *const ioChannel, const IbSize &size)
	: Drawable(size)
	, m_ioChannel(ioChannel)
	, m_rot(Rot0)
//	, m_size(size)
{
}

void DisplayBase::setRot(Rotation newRot)
{
	if (m_rot != newRot)
	{
		// Rot changed 0/180 <-> 90/270 then transpose
		if (((m_rot == Rot0 || m_rot == Rot180) && (newRot == Rot90 || newRot == Rot270))
				&& ((m_rot ==  Rot270 || m_rot == Rot90) && (newRot == Rot0 || newRot == Rot180))
		   )
		{
			m_size.transpose();
		}
	}
	m_rot = newRot;
}


