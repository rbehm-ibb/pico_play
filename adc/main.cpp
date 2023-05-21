// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 10/31/2022 by behm
// ******************************************************

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "../ibblib/debug.h"
#include "../ibblib/ledblink.h"
#include "../ibblib/gpioinit.h"
#include <hardware/adc.h>
#include <hardware/pwm.h>

#include "adc.h"

using namespace std;

const char version[] = "ADC 0.1" __DATE__ "-" __TIME__;
 static const IoDef io[] =
 {
	{ 0, IoDef::Out, 1, IoDef::None, "P0" },
	{ 1, IoDef::Out, 1, IoDef::None, "P1" },
	{ 2, IoDef::Out, 1, IoDef::None, "P2" },
	{ 3, IoDef::Out, 1, IoDef::None, "P3" },
	{ 4, IoDef::Out, 1, IoDef::None, "PWM4" },
	{ 5, IoDef::Out, 1, IoDef::None, "P5" },
	 { 22, IoDef::In, 1, IoDef::PUp, "But" },
	{ 26, IoDef::In, 1, IoDef::None, "A0" },
	{ 27, IoDef::In, 1, IoDef::None, "A1" },
	 { -1, IoDef::In, 0, IoDef::None, nullptr }
 };
 GpioInit gpio(io);

static void uif();
static void adcPoll();
static void __no_inline_not_in_flash_func(callback)(uint gpio, uint32_t event_mask);
static void showx();

static Adc *a0, *a1;

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
	adc_init();
	adc_gpio_init(26);
	adc_gpio_init(27);
//	adc_set_round_robin(0x03);
//	adc_run(true);

	a0 = new Adc(0);
	a1 = new Adc(1);
	gpio_set_function(4, GPIO_FUNC_PWM);
	pwm_config pwm = pwm_get_default_config();
	uint slice_num = pwm_gpio_to_slice_num(4);
	// Set period of 4 cycles (0 to 3 inclusive)
	const uint16_t khz8 = 15630;
	const uint16_t khz16 = khz8/2;
	pwm_set_wrap(slice_num, khz16);
	// Set channel A output high for one cycle before dropping
	pwm_set_chan_level(slice_num, PWM_CHAN_A, khz16/2);
	// Set initial B output high for three cycles before dropping
	pwm_set_chan_level(slice_num, PWM_CHAN_B, 3);
	// Set the PWM running
	pwm_set_enabled(slice_num, true);
	cout << "slice=" << slice_num << endl;
	gpio_set_irq_enabled_with_callback(4, GPIO_IRQ_EDGE_RISE, true, &callback);

	gpio.showGpio();
	while (1)
	{
		blink.poll();
//		adcPoll();
		uif();
	}
}

static void uif()
{
	const int c = getchar_timeout_us(0);
	if (c < 0)
		return;
	switch (c)
	{
	case '.':
		Debug::showSysInfo(version);
		gpio.showGpio();
		break;
	case 'a':
		adcPoll();
		break;
	case ',':
		showx();
		break;
	default:
		printf("rx=%04x\n", c);
	}
}

static void adcPoll()
{
	cout  << "ADC0:" << setw(10) << a0->scaled(a0->poll()) << " ADC1:" << setw(10) <<  a1->scaled(a1->poll()) << flush;
	cout << " 0:" << a0->min() << " " << a0->max();
	cout << " 1:" << a1->min() << " " << a1->max() << '\r' << flush;
}

static volatile int flag = 0;
static volatile uint pin = 0;
static volatile uint32_t mask = 0;

static void showx()
{
	cout << boolalpha << flag << " pin=" << pin << " mask=" << mask << endl;
}

static void __no_inline_not_in_flash_func(callback)(uint gpio, uint32_t event_mask)
{
	constexpr uint32_t xmask = 1;
	++flag;
	pin = gpio;
	mask = event_mask;
	gpio_acknowledge_irq(4, mask);
	gpio_xor_mask(xmask);
}
