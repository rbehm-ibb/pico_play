// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/17/2023 by behm
// ******************************************************

#ifndef GPIOINIT_H
#define GPIOINIT_H

#include <stdint.h>

struct IoDef
{
	enum Dir { In, Out };
	enum Pull { None, PUp, PDn };
	int8_t pin;
	Dir dir;
	int8_t init;
	Pull pull;
	const char *name;
};

class GpioInit
{
public:
	GpioInit(const IoDef *def);
	void init();
	void showGpio() const;
	void poll();
private:
	static const char *gpioConf(int n);
	const IoDef *  const m_io;
	uint32_t m_ports;
	uint32_t m_mask;
};

#endif // GPIOINIT_H
