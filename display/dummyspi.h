// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/27/2023 by behm
// ******************************************************

#ifndef DUMMYSPI_H
#define DUMMYSPI_H

#include "spibase.h"

class DummySpi : public SpiBase
{
public:
	DummySpi();

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
};

#endif // DUMMYSPI_H
