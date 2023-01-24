// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/24/2023 by behm
// ******************************************************

#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "spi1.h"


Spi1::Spi1(int cs, int cd, int res)
	: SpiBase()
	, m_cs(cs)
	, m_cd(cd)
	, m_res(res)
{
	gpio_init(m_cs);
	gpio_set_dir(m_cs, GPIO_OUT);
	Spi1::csOff();
	gpio_init(m_cd);
	gpio_set_dir(m_cd, GPIO_OUT);
	Spi1::cdOn();
	gpio_init(m_res);
	gpio_set_dir(m_res, GPIO_OUT);
	gpio_put(m_res, 0);
}

void Spi1::start()
{
	spi_init(spi1, 10 * 1000 * 1000);
	spi_set_format(spi1, 16, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);
	gpio_set_function(12, GPIO_FUNC_SPI);	// miso
	gpio_set_function(14, GPIO_FUNC_SPI);	// sck
	gpio_set_function(15, GPIO_FUNC_SPI);	// mosi
	Spi1::csOff();
	Spi1::cdOn();
	Spi1::reset();
}

void Spi1::csOn()
{
	waitSpi();
	gpio_put(m_cs, 0);
}

void Spi1::csOff()
{
	waitSpi();
	gpio_put(m_cs, 1);
}

void Spi1::cdOn()
{
	waitSpi();
	gpio_put(m_cd, 1);
}

void Spi1::cdOff()
{
	waitSpi();
	gpio_put(m_cd, 0);
}

void Spi1::reset()
{
	gpio_put(m_res, 0);
	busy_wait_ms(100);
	gpio_put(m_res, 1);
}

void Spi1::tx_blocking(uint16_t d)
{
	spi_write16_blocking(spi1, &d, 1);
}

void Spi1::tx(uint16_t d)
{
	while (! spi_is_writable(spi1))
	{}
	spi_write16_blocking(spi1, &d, 1);
}

void Spi1::tx(uint16_t cmd, const uint16_t *d, size_t count)
{
	cdOn();
	csOn();
	tx(cmd);
	cdOff();
	spi_write16_blocking(spi1, d, count);
	cdOff();
}
