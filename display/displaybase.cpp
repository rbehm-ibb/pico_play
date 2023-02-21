// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/24/2023 by behm
// ******************************************************

#include "displaybase.h"

DisplayBase::DisplayBase(SpiBase * const ioChannel, const IbSize &size)
	: m_ioChannel(ioChannel)
	, m_size(size)
{
}
