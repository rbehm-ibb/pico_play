// ******************************************************
// * copyright (C) 2024 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2024-02-03 by behm
// ******************************************************

#include <hardware/gpio.h>
#include "i2cdevice.h"

I2cDevice::I2cDevice(i2c_inst *i2c, uint sda, uint scl)
	: m_channel(i2c)
	, m_sda(sda)
	, m_scl(scl)
{
	i2c_init(m_channel, 400 * 1000);
	gpio_set_function(m_sda, GPIO_FUNC_I2C);
	gpio_set_function(m_scl, GPIO_FUNC_I2C);
	gpio_pull_up(m_sda);
	gpio_pull_up(m_scl);
}

bool I2cDevice::devOk(uint8_t addr)
{
	uint8_t dummy;
	int rc = i2c_read_blocking(m_channel, addr, &dummy, 1, true);
	return rc = 1;
}

int I2cDevice::write(uint8_t addr, const uint8_t *data, size_t len)
{
	uint8_t dummy;
	int rc = i2c_read_blocking(m_channel, addr, const_cast<uint8_t*>(data), len, true);
	return rc;
}

int I2cDevice::read(uint8_t addr, uint8_t *data, size_t len)
{
	uint8_t dummy;
	int rc = i2c_read_blocking(m_channel, addr, data, 1, true);
	return rc;
}
