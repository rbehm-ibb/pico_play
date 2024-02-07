// ******************************************************
// * copyright (C) 2024 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/6/2024 by behm
// ******************************************************

#include "i2cregister.h"

I2cRegister::I2cRegister(I2cDevice *dev, uint8_t reg, uint8_t size)
	: m_dev(dev)
	, m_reg(reg)
	, m_size(size)
{}

uint I2cRegister::read() const
{
	if (m_size ==  1)
	{
		return m_dev->readReg8(m_reg);
	}
	else
	{
		return m_dev->readReg16(m_reg);
	}
}

bool I2cRegister::write(uint d)
{
	if (m_size ==  1)
	{
		return m_dev->writeReg8(m_reg, d);
	}
	else
	{
		return m_dev->writeReg16(m_reg, d);
	}
}
