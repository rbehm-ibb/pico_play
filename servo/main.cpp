// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 10/31/2022 by behm
// ******************************************************

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
//#include "pico/stdlib.h"
//#include "hardware/gpio.h"
#include "../ibblib/debug.h"
#include "../ibblib/ledblink.h"
#include "../ibblib/gpioinit.h"
#include "servo.h"

using namespace std;

const char version[] = "Servo 0.1";
 static const IoDef io[] =
 {
	 { 0, IoDef::Out, 1, IoDef::PUp, "Tx" },
	 { -1, IoDef::In, 0, IoDef::None, nullptr }
 };
 GpioInit gpio(io);

static void uif();
servo_t servo;
uint8_t angle = 0;

int main()
{
	stdio_usb_init();
	gpio.init();
	LedBlink blink(PICO_DEFAULT_LED_PIN, 100);
	while (! stdio_usb_connected())
	{
		blink.poll();
	}
	blink.setTime(300);
	Debug::showSysInfo(version);
	servoAttach(&servo, 1);

	while (1)
	{
		blink.poll();
		uif();
	}
}

static void uif()
{
	const int c = getchar_timeout_us(0);
	if (c < 0)
		return;
	printf("rx=%04x\n", c);
	switch (c)
	{
	case '.':
		Debug::showSysInfo(version);
		gpio.showGpio();
		break;
	case '+':
		if (++angle > 180)
		{
			angle = 180;
		}
		servoWrite(&servo, angle);
		cout << "Angle=" << int(angle) << endl;
		break;
	case '-':
		if (angle > 0)
		{
			--angle;
		}
		servoWrite(&servo, angle);
		cout << "Angle=" << int(angle) << endl;
		break;
	}
}
