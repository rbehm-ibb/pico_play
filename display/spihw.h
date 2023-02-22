// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/3/2023 by behm
// ******************************************************


#ifndef SPIHW_H
#define SPIHW_H

#include "spibase.h"
#include "hardware/spi.h"

class SpiHw : public SpiBase
{
	struct HwDef
	{
		spi_inst_t * port;
		uint8_t Clk;
		uint8_t Mosi;
		uint8_t Miso;
		uint8_t Cs;
		uint8_t Cd;
		uint8_t Res;
	};

public:
	SpiHw(HwDef const &hw);

	// SpiBase interface
public:
	void start() override;
	void csOn() override;
	void csOff() override;
	void cdOn() override;
	void cdOff() override;
	void reset() override;
	void tx(uint8_t d) override;
	void tx(uint16_t d) override;
	void tx(uint8_t cmd, const uint8_t *d, size_t count) override;
	static const HwDef hwSpi0, hwSpi1;
protected:
	const HwDef m_hw;
};

#endif // SPIHW_H
