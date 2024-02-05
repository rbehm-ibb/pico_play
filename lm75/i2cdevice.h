// ******************************************************
// * copyright (C) 2024 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2024-02-03 by behm
// ******************************************************

#ifndef I2CDEVICE_H
#define I2CDEVICE_H

#include <hardware/i2c.h>

class I2cDevice
{
public:
	I2cDevice(i2c_inst *i2c, uint sda, uint scl);
	uint sda() const { return m_sda; }
	uint scl() const { return m_scl; }
	i2c_inst *channel() const { return m_channel; }
	uint hwIdx() const { return i2c_hw_index(m_channel); }
	bool devOk(uint8_t addr);
	int write(uint8_t addr, const uint8_t *data, size_t len);
	int read(uint8_t addr, uint8_t *data, size_t len);


protected:
	i2c_inst *const m_channel;
	const uint m_sda;
	const uint m_scl;
};

#endif // I2CDEVICE_H
