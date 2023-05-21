// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/20/2023 by behm
// ******************************************************

#ifndef ADC_H
#define ADC_H

#include <stdint.h>

class Adc
{
public:
	Adc(int ch);
	int poll();
	int scaled(int v);
	int min() const { return m_min; }
	int max() const { return m_max; }
private:
	const uint16_t m_ch;
	int m_min;
	int m_max;
};

#endif // DWG_H
