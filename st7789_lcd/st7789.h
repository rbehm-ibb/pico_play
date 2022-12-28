// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/28/2022 by behm
// ******************************************************

#ifndef ST7789_H
#define ST7789_H

#include "pico/stdlib.h"
#include "hardware/pio.h"

class St7789
{
public:
	St7789();
private:
	PIO pio = pio0;
	static constexpr uint sm = 0;
};

#endif // ST7789_H
