// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/24/2023 by behm
// ******************************************************

#ifndef SPIBASE_H
#define SPIBASE_H

#include <cstddef>
#include <stdint.h>

/// SpiBase a base class for alll usable SPI interfaces (HW, PIO, etc)
class SpiBase
{
public:
	SpiBase();
	virtual ~SpiBase();
	virtual void start() = 0;
	virtual void csOn() = 0;
	virtual void csOff() = 0;
	virtual void cdOn() = 0;
	virtual void cdOff() = 0;
	virtual void reset() = 0;
	virtual void tx_blocking(uint16_t d) = 0;
	virtual void tx(uint16_t d) = 0;
	virtual void tx(uint16_t cmd, const uint16_t *d, size_t count) = 0;
};

#endif // SPIBASE_H
