// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/24/2023 by behm
// ******************************************************

#ifndef SPI1_H
#define SPI1_H

#include "hardware/spi.h"
#include "spibase.h"

class Spi1 : public SpiBase
{
public:
	Spi1(int cs, int cd, int res);

	// SpiBase interface
public:
	virtual void start() override;
	virtual void csOn() override;
	virtual void csOff() override;
	virtual void cdOn() override;
	virtual void cdOff() override;
	virtual void reset() override;
	virtual void tx(uint8_t d) override;
	virtual void tx(uint16_t d) override;
	virtual void tx(uint8_t cmd, const uint8_t *d, size_t count) override;
	void waitSpi() { while (! spi_is_busy(spi1)) {}; }

private:
	const int m_cs;
	const int m_cd;
	const int m_res;

};

#endif // SPI1_H
