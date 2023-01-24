// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/20/2023 by behm
// ******************************************************

#ifndef DWG_H
#define DWG_H

#include <stdint.h>

class Dwg
{
public:
	Dwg(int pina, int pinb, int sw);
	bool poll();
private:
	const int m_pina;
	const int m_pinb;
	const int m_pins;
	uint8_t m_last;
	uint8_t m_lasts;
	int m_count;
	bool m_sw;
};

#endif // DWG_H
