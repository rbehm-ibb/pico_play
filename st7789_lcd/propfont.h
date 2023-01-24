// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/30/2022 by behm
// ******************************************************

#ifndef PROPFONT_H
#define PROPFONT_H

#include "ibfont.h"

class PropFont : public IbFont
{
public:
	PropFont();
	static PropFont font;
};


#endif // PROPFONT_H
