// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/20/2023 by behm
// ******************************************************

#include <iostream>
#include "adc.h"
#include "hardware/adc.h"

using namespace std;

Adc::Adc(int ch)
	: m_ch(ch)
	, m_min(4096)
	, m_max(0)
{
}

int Adc::poll()
{
	adc_select_input(m_ch);
	int v = adc_read();
	if (v < m_min)
	{
		m_min = v;
	}
	if (v > m_max)
	{
		m_max = v;
	}
	return v;
}

int Adc::scaled(int v)
{
	v -= m_min;
	float vx = v / float(m_max - m_min);
	vx *= 100.;
	return vx;
}
