// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/9/2023 by behm
// ******************************************************

#include <iostream>
#include <string.h>
#include "uartipc.h"

struct States
{
	const char *name;
	void (UartIpc::*state)(uint8_t rxd);
} states[] =
{
	{ "Idle", &UartIpc::rxIdle },
	{ "rxData", &UartIpc::rxData },
	{ "rxDle", &UartIpc::rxDle },
	{ "rxCrc", &UartIpc::rxCrc },
	{ nullptr, nullptr}
};

UartIpc::UartIpc(int uartIdx, int txPin, int rxPin, int baud)
	: Uart(uartIdx, txPin, rxPin, baud)
	, m_waitAck(false)
	, m_respTx(0)
{
	clearRx();
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
		std::cout << __PRETTY_FUNCTION__ << " state:" << name << " rxlen:" << m_rxbuffer.size() << " waitAck:" << m_waitAck << std::endl;
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
			Uart::put(char(ENQ));
			m_txTime = make_timeout_time_ms(5000);
		}
	}
	if (m_respTx)
	{
		std::cout << __PRETTY_FUNCTION__ << " RespTx:" << m_respTx << std::endl;
		Uart::put(m_respTx);
		m_respTx = 0;
	}
}

//int UartIpc::get(uint8_t *d)
//{
//	if (! m_hasRx)
//	{
//		return -1;
//	}
//	m_rxbuffer.clear();
//	int rxl = m_rxLen;
//	m_hasRx = 0;
//	return rxl;
//}

std::vector<uint8_t> UartIpc::get()
{
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
	m_txbuffer = d;
	uint8_t crc = 0;
	Uart::put(char(STX));
	for (const uint8_t c : d)
	{
		if (c == DLE)
		{
			Uart::put(c);
		}
		Uart::put(c);
		crc += c;
	}
	Uart::put(char(DLE));
	Uart::put(char(ETX));
	Uart::put(crc);
	m_respRxd = 0;
	m_waitAck = true;
	m_txTime = make_timeout_time_ms(1000);
	return true;
}


void UartIpc::uartIsr()
{
	while (uart_is_readable(m_uart))
	{
		const uint8_t c = uart_getc(m_uart);
		(this->*m_rxState)(c);
	}
}

void UartIpc::clearRx()
{
	memset(m_rxbuffer, 0, sizeof(m_rxbuffer));
	m_rxLen = 0;
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
			m_respTx = NAK;
			break;
		}
		m_rxLen = 0;
		m_rxCrc = 0;
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
		return;
	}
	m_rxState = &UartIpc::rxData;
	addRxData(c);
}

void UartIpc::rxCrc(uint8_t c)
{
	m_rxCrc = '#';
	if (c == m_rxCrc)
	{
//		Uart::put(char(ACK));
		m_respTx = ACK;
		m_hasRx = true;
	}
	else
	{
		m_respTx = NAK;
	}
}

void UartIpc::addRxData(uint8_t c)
{
	if (m_rxLen >= MaxLen)
	{
//		Uart::put(char(NAK));
		m_respTx = NAK;
		m_rxState = &UartIpc::rxIdle;
		return;
	}
	m_rxbuffer[m_rxLen++] = c;
	m_rxCrc += c;
}
