// ******************************************************
// * copyright (C) 2024 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/5/2024 by behm
// ******************************************************

// #include <iostream>
#include "i2cdevice.h"

using namespace std;

I2cDevice::I2cDevice(I2cChannel *channel, uint8_t addr)
	: m_channel(channel)
	, m_addr(addr)
{}

bool I2cDevice::exist() const
{
	return m_channel->devOk(m_addr);
}

int I2cDevice::readReg8(uint8_t reg)
{
	m_channel->write(m_addr, &reg, 1);
	return m_channel->read(m_addr, &reg, 1) ==  1 ? reg : -1;
}

int I2cDevice::readReg16(uint8_t reg)
{
	uint8_t regD[2];
	// cout << " " << __PRETTY_FUNCTION__ << ":" << int(reg);
	m_channel->write(m_addr, &reg, 1);
	// cout << " " << ":" << int(reg) << "->" << dec << rc;
	if (m_channel->read(m_addr, regD, 2) == 2)
	{
		// cout << hex << " " << int(regD[0]) << " " << int(regD[1]) << dec << endl;
		return 256 * regD[0] + regD[1];
	}
	return -1;
}

bool I2cDevice::writeReg8(uint8_t reg, uint8_t val)
{
	uint8_t d[2] = { reg, val };
	return m_channel->write(m_addr, d, 2) == 2;
}

bool I2cDevice::writeReg16(uint8_t reg, uint16_t val)
{
	uint8_t d[3] = { reg, uint8_t(val >> 8), uint8_t(val) };
	return m_channel->write(m_addr, d, 3) == 3;
}
