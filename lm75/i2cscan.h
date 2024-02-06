// ******************************************************
// * copyright (C) 2024 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/6/2024 by behm
// ******************************************************

#ifndef I2CSCAN_H
#define I2CSCAN_H

#include "i2cchannel.h"

class I2cScan
{
public:
	I2cScan(I2cChannel *chan);
	void scan();
private:
	I2cChannel * const m_channel;
};

#endif	  // I2CSCAN_H
