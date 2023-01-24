// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/20/2023 by behm
// ******************************************************

#include <iostream>
#include "dwg.h"
#include "hardware/gpio.h"

using namespace std;

Dwg::Dwg(int pina, int pinb, int sw)
	: m_pina(pina)
	, m_pinb(pinb)
	, m_pins(sw)
	, m_count(0)
	, m_sw(false)
{
	gpio_init(m_pina);
	gpio_set_dir(m_pina, false);
	gpio_set_pulls(m_pina, true, false);
	gpio_init(m_pinb);
	gpio_set_dir(m_pinb, false);
	gpio_set_pulls(m_pinb, true, false);
	gpio_init(m_pins);
	gpio_set_dir(m_pins, false);
	gpio_set_pulls(m_pins, true, false);
	m_last = 0;
	if (gpio_get(m_pina))
	{
		m_last |= 1 << 0;
	}
	if (gpio_get(m_pinb))
	{
		m_last |= 1 << 1;
	}
	m_lasts = gpio_get(m_pins);
}

bool Dwg::poll()
{
	uint8_t in = 0;
	if (gpio_get(m_pina))
	{
		in |= 1 << 0;
	}
	if (gpio_get(m_pinb))
	{
		in |= 1 << 1;
	}
	bool changed = false;
	if (m_last != in)
	{
		uint8_t diff = (m_last << 2) | in;
		switch (diff)
		{
		case 1:
		case 4:
		case 7:
		case 13:
			++m_count;
			changed = true;
			break;
		case 2:
		case 8:
		case 11:
		case 14:
			--m_count;
			changed = true;
			break;
		}
		cout << __PRETTY_FUNCTION__ << " d=" << int(diff) << " c=" << m_count << endl;
		m_last = in;
	}
	bool sw = gpio_get(m_pins);
	if (m_lasts != sw)
	{
		cout << __PRETTY_FUNCTION__ << " l=" << int(m_lasts) << " i=" << int(sw) << endl;
		m_lasts = sw;
		changed = true;
	}
	return changed;
}
