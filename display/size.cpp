// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/24/2023 by behm
// ******************************************************

#include "size.h"

//namespace IbDisp
//{

std::ostream &operator<<(std::ostream &s, const IbSize &sz)
{
	return s << "S[" << sz.w() << ',' << sz.h() << ']';
}

//} // namesoace
