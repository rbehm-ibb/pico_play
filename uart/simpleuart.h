// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/9/2023 by behm
// ******************************************************

#ifndef SIMPLEUART_H
#define SIMPLEUART_H

#include "safequeue.h"
#include "uartbase.h"

///
/// \brief The SimpleUart class is a simple char based Uart
/// It handles rx-interrupt and places rx data into a queue
/// to be retrieved by get()/hasRx().
/// Sending is handled by put(..) functions, non interrupt based.
///
/// Setup of the hardware is done by the base class.
///
class SimpleUart : public UartBase
{
public:
	SimpleUart(int uartIdx, int txPin =  -1, int rxPin = -1, int baud = 115200);
	virtual ~SimpleUart();
	bool hasrx() { return ! m_rxq.isEmpty(); }
	uint8_t get();
	bool canTx();
	bool put(uint8_t c);
	bool put(char c) { return put(uint8_t(c)); }
	void put(const char *s);
	void put(const uint8_t *s, size_t n);
protected:
	static constexpr int qsize = 100;
	SafeQueue m_rxq;
	void uartIsr() override;
};

#endif // SIMPLEUART_H
