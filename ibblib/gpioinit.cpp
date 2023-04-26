// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/17/2023 by behm
// ******************************************************

#include <stdio.h>
#include "hardware/gpio.h"
#include "gpioinit.h"

GpioInit::GpioInit(const IoDef *def)
	: m_io(def)
	, m_ports(0)
{
}

void GpioInit::init()
{
	m_mask = 0;
	for (const IoDef *def = m_io; def->pin >= 0; ++def)
	{
		if (def->name)
		{
			gpio_init(def->pin);
			gpio_set_dir(def->pin, def->dir == IoDef::Out);
			gpio_put(def->pin, def->init);
			gpio_set_pulls(def->pin, def->pull == IoDef::PUp, def->pull == IoDef::PDn);
			m_mask |=  1U << def->pin;
		}
	}
//	printf("mask=%017b\n", m_mask);
}

void GpioInit::showGpio() const
{
	for (const IoDef *def = m_io; def->pin >= 0; ++def)
	{
		if (def->name)
		{
			const int pin = def->pin;
			const char *f = gpioConf(pin);
			const char *up  = gpio_is_pulled_up(pin) ? "Up" : "- ";
			const char *dn  = gpio_is_pulled_down(pin) ? "Dn" : "- ";
			printf("%02d:%-6s -%s %-3s u=%s, d=%s v=%d\n", pin, def->name, f, (gpio_get_dir(pin) ? "OUT" : "IN"), up, dn, gpio_get(pin));
		}
	}
}

void GpioInit::poll()
{
	uint32_t p  = gpio_get_all() & m_mask;
	uint32_t diff = (p ^ m_ports) & m_mask;
	if (diff)
	{
		printf("p=%017b d=%017b", p, diff);
		m_ports = p;
		for (const IoDef *def = m_io; def->pin >= 0; ++def)
		{
			uint32_t m = 1UL << def->pin;
			if (diff & m)
			{
				printf(",%s=%d", def->name, !!(p & m));
			}
		}
		printf("\n");
	}
}

const char *GpioInit::gpioConf(int n)
{
	static const struct FctTab
	{
		gpio_function fct;
		const char *name;
	} gpioTab[] =
	{
		{ GPIO_FUNC_XIP, "GPIO_FUNC_XIP" },
		{ GPIO_FUNC_SPI, "GPIO_FUNC_SPI" },
		{ GPIO_FUNC_UART, "GPIO_FUNC_UART" },
		{ GPIO_FUNC_I2C, "GPIO_FUNC_I2C" },
		{ GPIO_FUNC_PWM, "GPIO_FUNC_PWM" },
		{ GPIO_FUNC_SIO, "GPIO_FUNC_SIO" },
		{ GPIO_FUNC_PIO0, "GPIO_FUNC_PIO0" },
		{ GPIO_FUNC_PIO1, "GPIO_FUNC_PIO1" },
		{ GPIO_FUNC_GPCK, "GPIO_FUNC_GPCK" },
		{ GPIO_FUNC_USB, "GPIO_FUNC_USB" },
		{ GPIO_FUNC_NULL, "GPIO_FUNC_NULL" },
		{ GPIO_FUNC_NULL, nullptr}
	};
	static char s[30];
	gpio_function f = gpio_get_function(n);
	for (const FctTab *p = gpioTab; p->name; ++p)
	{
		if (f == p->fct)
		{
			sprintf(s, "%02x %14s", f, p->name);
			return s;
		}
	}
	sprintf(s, "%d UNDEF", f);
	return s;
}
