// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/7/2022 by behm
// ******************************************************

#include "debug.h"
#include <stdio.h>
#include <string.h>
#include "pico/unique_id.h"

void Debug::dump(const void *src, size_t size, const char *title)
{
	if (title)
	{
		printf("%s\n", title);
	}
	const uint8_t *p = static_cast<const uint8_t *>(src);
	char line[4 * 16 + 20];
	for (uint i = 0; i < size; i += 16, p += 16)
	{
		memset(line, ' ', sizeof(line));
		line[sizeof (line) - 1] = '\0';
		for (uint j = 0; j < 16; ++j)
		{
			if (i + j >= size)
			{
				break;
			}
			char s[3];
			char *pp = &line[j * 3];
			sprintf(s, "%02x", p[j]);
			pp[0] = s[0];
			pp[1] = s[1];

			uint8_t c = p[j];
			if (c < ' ' ||  c >= 0x7f)
			{
				c = '.';
			}
			line[3 * 16 + 1 + j] = c;
		}
		printf("%p: %s\n", p, line);
	}
}

void Debug::dump(const std::vector<uint8_t> &d, const char *title)
{
	dump(d.data(), d.size(), title);
}

void Debug::dump(const std::vector<uint16_t> &d, const char *title)
{
#ifdef SWAP
	vector<uint16_t> dd(d);
	for (uint16_t &db : dd)
	{
		db = __builtin_bswap16(db);
	}
	dump(dd.data(), dd.size()*sizeof(uint16_t), title);
#else
	dump(d.data(), d.size()*sizeof(uint16_t), title);
#endif
}

void Debug::showSysInfo(const char *version)
{
	extern char __flash_binary_end;
	printf("\f%s\nBOARD=<%s> SDK Version %s, Chip=%d, Rom=%d\n", version, PICO_BOARD, PICO_SDK_VERSION_STRING,  rp2040_chip_version(), rp2040_rom_version());
	char s[20];
	pico_get_unique_board_id_string(s, sizeof(s) - 1);
	uint l = &__flash_binary_end - ((char *)XIP_BASE);
	printf("id=<%s> pgmsize=%u/%uk Flashsize=%dM\n", s, l, l / 1024, PICO_FLASH_SIZE_BYTES / 1024 / 1024);
}
