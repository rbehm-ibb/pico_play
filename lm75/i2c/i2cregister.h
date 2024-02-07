// ******************************************************
// * copyright (C) 2024 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/6/2024 by behm
// ******************************************************

#ifndef I2CREGISTER_H
#define I2CREGISTER_H

#include "i2cdevice.h"

class I2cRegister
{
public:
	I2cRegister(I2cDevice *dev, uint8_t reg, uint8_t size);
	uint read() const;
	bool write(uint d);
private:
	I2cDevice * const m_dev;
	const uint8_t m_reg;
	const uint8_t m_size;
};

#endif	  // I2CREGISTER_H
