// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 11/1/2022 by behm
// ******************************************************

#ifndef CORE1_H
#define CORE1_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
//#include "pico/binary_info.h"
#include "hardware/uart.h"
#include "pico/multicore.h"


class core1
{
public:
	core1();
	static void run();
private:

	static void out(int n);
};

#endif // CORE1_H
