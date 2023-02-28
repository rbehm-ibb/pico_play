// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/27/2023 by behm
// ******************************************************

#include <iostream>
#include "dummyspi.h"

using namespace std;

DummySpi::DummySpi()
{
	cout << __PRETTY_FUNCTION__ << endl;
}


void DummySpi::start()
{
	cout << __PRETTY_FUNCTION__ << endl;
}

void DummySpi::csOn()
{
	cout << __PRETTY_FUNCTION__ << endl;
}

void DummySpi::csOff()
{
	cout << __PRETTY_FUNCTION__ << endl;
}

void DummySpi::cdOn()
{
	cout << __PRETTY_FUNCTION__ << endl;
}

void DummySpi::cdOff()
{
	cout << __PRETTY_FUNCTION__ << endl;
}

void DummySpi::reset()
{
	cout << __PRETTY_FUNCTION__ << endl;
}

void DummySpi::tx(uint8_t d)
{
	cout << __PRETTY_FUNCTION__ << " :" << hex << int(d) << dec << endl;
}

void DummySpi::tx(uint16_t d)
{
	cout << __PRETTY_FUNCTION__  << " :" << hex << int(d) << dec << endl;
}

void DummySpi::tx(uint8_t cmd, const uint8_t *d, size_t count)
{
	cout << __PRETTY_FUNCTION__ << " :"  << hex << int(cmd);
	for (uint i = 0; i < count; ++i)
	{
		cout << " ," << int(*d++);
	}
	cout << dec << endl;
}
