// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/3/2023 by behm
// ******************************************************

#include <iostream>
#include "spihw.h"
#include "hardware/gpio.h"

const SpiHw::HwDef SpiHw::hwSpi0 =
{
	.port = spi0,
	.Clk  = PICO_DEFAULT_SPI_SCK_PIN,
	.Mosi = PICO_DEFAULT_SPI_TX_PIN,
	.Miso = PICO_DEFAULT_SPI_RX_PIN,
	.Cs = PICO_DEFAULT_SPI_CSN_PIN,
	.Cd = 5,
	.Res = 0
};
const SpiHw::HwDef SpiHw::hwSpi1 =
{
	.port = spi1,
	.Clk  =14,
	.Mosi = 15,
	.Miso = 12,
	.Cs = 0,
	.Cd = 0,
	.Res = 0
};

SpiHw::SpiHw(HwDef const &hw)
	: SpiBase()
	, m_hw(hw)
{
	std::cout << __PRETTY_FUNCTION__
	     << " Mosi=" << int(m_hw.Mosi) << " Miso=" << int(m_hw.Miso) << " Sck=" << int(m_hw.Clk) << " port="
	     << spi_get_index(m_hw.port) << " cs=" << int(m_hw.Cs) << " cd=" << int(m_hw.Cd) << " res=" << int(m_hw.Res) << std::endl;
	gpio_init(m_hw.Cs);
	gpio_set_dir(m_hw.Cs, GPIO_OUT);
	gpio_put(m_hw.Cs, 1);
	gpio_init(m_hw.Cd);
	gpio_set_dir(m_hw.Cd, GPIO_OUT);
	gpio_put(m_hw.Cd, 0);
	gpio_init(m_hw.Res);
	gpio_set_dir(m_hw.Res, GPIO_OUT);
	gpio_put(m_hw.Res, 0);
}


void SpiHw::start()
{
	spi_set_format(m_hw.port, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
//	gpio_set_function(m_hw.Miso, GPIO_FUNC_SPI);	// miso
	gpio_set_function(m_hw.Clk, GPIO_FUNC_SPI);	// sck
	gpio_set_function(m_hw.Mosi, GPIO_FUNC_SPI);	// mosi
	spi_init(m_hw.port, 1 * 100 * 1000);
	csOff();
	cdOn();
	reset();
}

void SpiHw::csOn()
{
}

void SpiHw::csOff()
{
}

void SpiHw::cdOn()
{
}

void SpiHw::cdOff()
{
}

void SpiHw::reset()
{
}

void SpiHw::tx_blocking(uint16_t d)
{
}

void SpiHw::tx(uint16_t d)
{
}

void SpiHw::tx(uint16_t cmd, const uint16_t *d, size_t count)
{
}
