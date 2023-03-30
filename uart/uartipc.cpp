// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/9/2023 by behm
// ******************************************************

#include <iostream>
#include <string.h>
#include "pico/time.h"
#include "uartipc.h"
#include "hardware/gpio.h"

struct UartIpc::States UartIpc::states[5] =
{
	{ "Idle", &UartIpc::rxIdle },
	{ "rxData", &UartIpc::rxData },
	{ "rxDle", &UartIpc::rxDle },
	{ "rxCrc", &UartIpc::rxCrc },
	{ nullptr, nullptr}
};

UartIpc::UartIpc(int uartIdx, int txPin, int rxPin, int baud)
	: UartBase(uartIdx, txPin, rxPin, baud)
	, m_waitAck(false)
	, m_respTx(0)
{
	clearRx();
	m_rxState = &UartIpc::rxIdle;
	m_repeat =  0;
}

void UartIpc::poll()
{
	static void (UartIpc::*rxState)(uint8_t rxd) = nullptr;
	if (m_rxState != rxState)
	{
		rxState = m_rxState;
		const char *name = "??";
		for (const States *p = states; p->name; ++p)
		{
			if (m_rxState == p->state)
			{
				name = p->name;
				break;
			}
		}
		std::cout << __PRETTY_FUNCTION__ << " state:" << name << " rxlen:" << m_rxbuffer.size() << " waitAck:" << m_waitAck << " rtx:" << m_respTx << std::endl;
	}
	if (m_waitAck)
	{
		if (m_respRxd)
		{
			std::cout << __PRETTY_FUNCTION__ << " RespRx:" << m_respRxd << std::endl;
			m_waitAck = false;
		}
		if (time_reached(m_txTime))
		{
			std::cout << __PRETTY_FUNCTION__ << "timeout ACK" << std::endl;
			if (++m_repeat > 5)
			{
				UartBase::put(char(ENQNAK));
				m_waitAck = false;
			}
			else
			{
				UartBase::put(char(ENQ));
				m_txTime = make_timeout_time_ms(5000);
			}
		}
	}
	if (m_respTx)
	{
		std::cout << __PRETTY_FUNCTION__ << " RespTx:" << m_respTx  << " " << std::hex << int(m_rxCrc) << '.' << int(m_hadCrc) << std::dec << std::endl;
		UartBase::put(m_respTx);
		m_respTx = 0;
	}
}

std::vector<uint8_t> UartIpc::get()
{
	std::cout << __PRETTY_FUNCTION__ << " hasrx=" << m_hasRx << std::endl;
	std::vector<uint8_t> res;
	if (m_hasRx)
	{
		res = m_rxbuffer;
		m_hasRx = false;
		m_respTx = ACK;
	}
	return res;
}

bool UartIpc::put(const uint8_t *d, size_t l)
{
	if (m_waitAck)
	{
		return false;
	}
	m_repeat = 0;
	std::vector<uint8_t> v;
	v.reserve(l);
	for (uint i =  0; i < l; ++i)
	{
		v.push_back(d[i]);
	}
	return put(v);
}

bool UartIpc::put(std::vector<uint8_t> d)
{
	if (m_waitAck)
	{
		return false;
	}
	m_repeat = 0;
	m_txbuffer = d;
	uint8_t crc = STX;
	UartBase::put(char(STX));
	for (const uint8_t c : d)
	{
		if (c == DLE)
		{
			UartBase::put(c);
		}
		UartBase::put(c);
		crc += c;
	}
	UartBase::put(char(DLE));
	UartBase::put(char(ETX));
	crc += ETX;
	UartBase::put(crc);
	m_respRxd = 0;
	m_waitAck = true;
	m_txTime = make_timeout_time_ms(1000);
	return true;
}


void UartIpc::uartIsr()
{
	const uint32_t mask1 = 1U << 2;
	const uint32_t mask2 = 1U << 3;
	bool on = uart_get_dreq(m_uart, 1);
	while (uart_is_readable(m_uart))
	{
		const uint8_t c = uart_getc(m_uart);
		(this->*m_rxState)(c);
	}
}

void UartIpc::clearRx()
{
	m_rxbuffer.clear();
	m_hasRx = false;
	m_rxState = &UartIpc::rxIdle;
}

void UartIpc::rxIdle(uint8_t c)
{
	switch (c)
	{
	case ACK:
	case NAK:
	case WACK:
		m_respRxd = c;
		break;
	case STX:
		if (m_hasRx)
		{
			m_respTx = NAK | 0x80;
			break;
		}
		m_rxbuffer.clear();	// start from 0
		m_rxCrc = STX;
		m_rxState = &UartIpc::rxData;
		break;
	}
}

void UartIpc::rxData(uint8_t c)
{
	if (c == DLE)
	{
		m_rxState = &UartIpc::rxDle;
		return;
	}
	addRxData(c);
}

void UartIpc::rxDle(uint8_t c)
{
	if (c == ETX)
	{
		m_rxState = &UartIpc::rxCrc;
		m_rxCrc += c;
		return;
	}
	m_rxState = &UartIpc::rxData;
	addRxData(c);
}

void UartIpc::rxCrc(uint8_t c)
{
//	m_rxCrc = '#';
	m_hadCrc = c;
	if (c == m_rxCrc)
	{
//		Uart::put(char(ACK));
		m_respTx = WACK;
		m_hasRx = true;
	}
	else
	{
		m_respTx = NAK;
	}
	m_rxState = &UartIpc::rxIdle;
}

void UartIpc::addRxData(uint8_t c)
{
	if (m_rxbuffer.size() >= MaxLen)
	{
//		Uart::put(char(NAK));
		m_respTx = NAK;
		m_rxState = &UartIpc::rxIdle;
		return;
	}
	m_rxbuffer.push_back(c);
	m_rxCrc += c;
}
