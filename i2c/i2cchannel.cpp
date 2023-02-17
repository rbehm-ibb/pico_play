// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/17/2023 by behm
// ******************************************************

#include "i2cchannel.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"

static struct ChDefs
{
	i2c_inst_t *ch;
	int8_t sda;
	int8_t scl;
} stdI2c[] =
{
	{ i2c0, 0, 0 },
	{ i2c1, 6, 7},
	{ nullptr, -1, -1}
};

static inline i2c_inst_t *getI2ct(int num)
{
	if (num < 0)
	{
		num =  PICO_DEFAULT_I2C;
	}
	return stdI2c[num].ch;
}

static inline int getSda(int ch, int sdain)
{
	if (sdain >= 0)
	{
		return sdain;
	}
	return stdI2c[ch].sda;
}

static inline int getScl(int ch, int sclin)
{
	if (sclin >= 0)
	{
		return sclin;
	}
	return stdI2c[ch].scl;
}

I2cChannel::I2cChannel(int num, int speed, int sda, int scl)
	: m_num(num < 0 ? PICO_DEFAULT_I2C : num)
	, m_ch(getI2ct(m_num))
	, m_sda(getSda(m_num, sda))
	, m_scl(getScl(m_num, scl))
{
	i2c_init(m_ch, speed);
	gpio_set_function(m_sda, GPIO_FUNC_I2C);
	gpio_set_function(m_scl, GPIO_FUNC_I2C);
	gpio_pull_up(m_sda);
	gpio_pull_up(m_scl);
}

bool I2cChannel::write(const uint8_t d, bool ack)
{
	return false;
}

bool I2cChannel::read(uint8_t &d, bool ack)
{
	return false;
}
