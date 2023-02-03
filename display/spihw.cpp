// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/3/2023 by behm
// ******************************************************

#include <iostream>
#include "spihw.h"

const SpiHw::HwDef SpiHw::hwSpi0 =
{
	.port = spi0,
	.Clk  = PICO_DEFAULT_SPI_SCK_PIN,
	.Mosi = PICO_DEFAULT_SPI_TX_PIN,
	.Miso = PICO_DEFAULT_SPI_RX_PIN,
	.Cs = 0,
	.Cd = 0,
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

}


void SpiHw::start()
{
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
