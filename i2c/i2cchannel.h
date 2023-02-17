// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/17/2023 by behm
// ******************************************************

#ifndef I2CCHANNEL_H
#define I2CCHANNEL_H

#include <stdint.h>
#include "hardware/i2c.h"

class I2cChannel
{
public:
	I2cChannel(int num, int speed, int sda=-1, int scl=-1);
	bool write(const uint8_t d, bool ack);
	bool read(uint8_t &d, bool ack);
private:
	const int m_num;
	i2c_inst_t *const m_ch;
	const int m_sda;
	const int m_scl;
};

#endif // I2CCHANNEL_H
