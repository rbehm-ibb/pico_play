// ******************************************************
// * copyright (C) 2024 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/5/2024 by behm
// ******************************************************

#ifndef I2CDEVICE_H
#define I2CDEVICE_H

#include "i2cchannel.h"

class I2cDevice
{
public:
	I2cDevice(I2cChannel *channel, uint8_t addr);
	bool exist() const;
	int readReg8(uint8_t reg);
	int readReg16(uint8_t reg);
	bool writeReg8(uint8_t reg, uint8_t val);
	bool writeReg16(uint8_t reg, uint16_t val);

protected:
	I2cChannel *const m_channel;
	const uint8_t m_addr;
};

#endif	  // I2CDEVICE_H
