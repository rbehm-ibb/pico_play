// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/30/2022 by behm
// ******************************************************

#ifndef FONT8X16_H
#define FONT8X16_H

#include "ibfont.h"

class Font8x16 : public IbFont
{
public:
	Font8x16();
	static Font8x16 font;
};

#endif // FONT8X16_H
