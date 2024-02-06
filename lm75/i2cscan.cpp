// ******************************************************
// * copyright (C) 2024 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/6/2024 by behm
// ******************************************************

#include <iostream>
// #include <iomanip>
#include "i2cscan.h"

using namespace std;

I2cScan::I2cScan(I2cChannel *chan)
	: m_channel(chan)
{
}

static bool reserved_addr(uint8_t addr)
{
	return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

void I2cScan::scan()
{
	cout << __PRETTY_FUNCTION__ << endl;
	for (int addr = 0; addr < (1 << 7); ++addr)
	{
		if (reserved_addr(addr))
		{
			continue;
		}
		if (m_channel->devOk(addr))
		{
			const char *name = "??";
			switch (addr)
			{
			case 0x3c:
				name = "OLED 1306";
				break;
			case 0x48:
				name = "LM75";
				break;
			case 0x51:
				name = "PCF8563 RTC";
				break;
			case 0x76:
			case 0x77:
				name = "BMP280";
				break;
			case 0x68:
				name = "MPU9250";
				break;
			case 0x40:
				name = "Baro Si7021";
				break;
			}

			cout << hex << showbase << addr << " " << name << endl;
		}
	}

}
