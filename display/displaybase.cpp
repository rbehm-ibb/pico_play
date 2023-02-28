// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/24/2023 by behm
// ******************************************************

#include <iostream>
#include "displaybase.h"
#include "pico/sync.h"

DisplayBase::DisplayBase(SpiBase *const ioChannel, const IbSize &size)
	: Drawable(size)
	, m_ioChannel(ioChannel)
	, m_rot(Rot0)
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

void DisplayBase::sendInitSeq(const uint8_t *list)
{
	while (*list != 0xff)
	{
		uint8_t cmd = *list++;
		uint8_t count = *list++;
		if (count & 0x80)
		{
			m_ioChannel->tx(cmd);
			std::cout << __PRETTY_FUNCTION__ << std::hex << int(cmd) << std::dec << " del " << int(*list) << std::dec << std::endl;
			busy_wait_ms(*list++);

		}
		else
		{
			m_ioChannel->tx(cmd, list, count);
			list += count;
		}
	}
}


