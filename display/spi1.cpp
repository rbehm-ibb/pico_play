// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/24/2023 by behm
// ******************************************************

#include <iostream>
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "spi1.h"

using namespace std;

//static spi_inst_t *spidev = spi0;
static spi_inst_t * const spidev = spi1;
constexpr int Mosi = 15;
constexpr int Miso = 12;
constexpr int Sck  =14;


Spi1::Spi1(int cs, int cd, int res)
	: m_cs(cs)
	, m_cd(cd)
	, m_res(res)
{
	cout << __PRETTY_FUNCTION__ << " cs=" << m_cs << " cd=" << m_cd << " res=" << m_res << endl;
	cout << "Mosi=" << Mosi << " Miso=" << Miso << " Sck=" << Sck << " port=" << spi_get_index(spidev) << endl;
	gpio_init(m_cs);
	gpio_set_dir(m_cs, GPIO_OUT);
	gpio_put(m_cs, 1);
	gpio_init(m_cd);
	gpio_set_dir(m_cd, GPIO_OUT);
	gpio_put(m_cd, 0);
	gpio_init(m_res);
	gpio_set_dir(m_res, GPIO_OUT);
	gpio_put(m_res, 0);
}

void Spi1::start()
{
	spi_set_format(spidev, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
	gpio_set_function(Miso, GPIO_FUNC_SPI);	// miso
	gpio_set_function(Sck, GPIO_FUNC_SPI);	// sck
	gpio_set_function(Mosi, GPIO_FUNC_SPI);	// mosi
	spi_init(spidev, 1 * 100 * 1000);
	Spi1::csOff();
	Spi1::cdOn();
	Spi1::reset();
}

void Spi1::csOn()
{
//	waitSpi();
	gpio_put(m_cs, 0);
}

void Spi1::csOff()
{
//	waitSpi();
	gpio_put(m_cs, 1);
}

void Spi1::cdOn()
{
//	waitSpi();
	gpio_put(m_cd, 1);
}

void Spi1::cdOff()
{
//	waitSpi();
	gpio_put(m_cd, 0);
}

void Spi1::reset()
{
	gpio_put(m_res, 0);
	busy_wait_ms(100);
	gpio_put(m_res, 1);
}

void Spi1::tx(uint8_t d)
{
	spi_write_blocking(spidev, &d, 1);
}

void Spi1::tx(uint16_t d)
{
	uint8_t *dd = (uint8_t*)(&d);
	spi_write_blocking(spidev, dd, 2);
}

void Spi1::tx(uint8_t cmd, const uint8_t *d, size_t count)
{
	cdOn();
	csOn();
	tx(cmd);
	cdOff();
	spi_write_blocking(spidev, d, count);
	csOff();
}
