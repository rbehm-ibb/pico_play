// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/7/2022 by behm
// ******************************************************

#include "debug.h"
#include <stdio.h>
#include <string.h>
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "pico/unique_id.h"
#include "hardware/flash.h"


Debug::Debug()
{

}

void Debug::dump(const void *src, size_t size, const char *title)
{
	if (title)
	{
		printf("%s\n", title);
	}
	const uint8_t *p = static_cast<const uint8_t*>(src);
	char line[4*16 + 20];
	for (uint i = 0; i < size; i += 16, p += 16)
	{
		memset(line, ' ', sizeof(line));
		line[sizeof (line) - 1] = '\0';
		for (uint j = 0; j < 16; ++j)
		{
			if (i+j >= size)
			{
				break;
			}
			char s[3];
			char *pp = &line[j*3];
			sprintf(s, "%02x", p[j]);
			pp[0] = s[0];
			pp[1] = s[1];

			uint8_t c = p[j];
			if (c < ' ' ||  c >= 0x7f)
			{
				c = '.';
			}
			line[3*16 + 1+j] = c;
		}
			printf("%p: %s\n", p, line);
	}
}

const char *Debug::gpioConf(int n)
{
	static const struct FctTab
	{
		gpio_function fct;
		const char *name;
	} gpioTab[] =
	{
		{GPIO_FUNC_XIP, "GPIO_FUNC_XIP" },
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
			sprintf(s, "%02x %s", f, p->name);
			return s;
		}
	}
	sprintf(s, "%d UNDEF", f);
	return s;
}

void Debug::showIos()
{
	for (int i = 0; i <= 29; ++i)
	{
		const char *f = gpioConf(i);
		int str = gpio_get_drive_strength(i);
		printf("%02d -> %s\t%s\tv=%d\n", i, f, (gpio_get_dir(i) ? "OUT" : "IN"), gpio_get(i));
	}
}

void Debug::showSysInfo(const char *version)
{
	extern char __flash_binary_end;
	printf("\f%s\nSDK Version %s\n", version, PICO_SDK_VERSION_STRING);
	char s[20];
	pico_get_unique_board_id_string(s, sizeof(s) - 1);
	uint l = &__flash_binary_end - ((char *)XIP_BASE);
	printf("<%s> l=%u/%uk FSz=%dM\n", s, l, l/1024, PICO_FLASH_SIZE_BYTES / 1024 / 1024);
}
