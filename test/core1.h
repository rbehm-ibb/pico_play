// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 11/1/2022 by behm
// ******************************************************

#ifndef CORE1_H
#define CORE1_H

#include <stdio.h>
#include "pico/stdlib.h"


class core1
{
public:
	core1();
	static void start();
private:
	static void run();
	static void out(int n);
};

#endif // CORE1_H
