// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/24/2023 by behm
// ******************************************************

#include "ibpoint.h"

std::ostream &operator<<(std::ostream &s, const IbPoint &p)
{
	return s << "P[" << p.x() << ',' << p.y() << ']';
}
