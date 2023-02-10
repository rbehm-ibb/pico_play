// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/9/2023 by behm
// ******************************************************

#ifndef UARTIPC_H
#define UARTIPC_H

#include <vector>
#include "uart.h"

class UartIpc : public Uart
{
public:
	enum Ctrl { STX='s', ETX='e', DLE='d', ACK='a', NAK='n', ENQ='?', WACK='w' };
	UartIpc(int uartIdx, int txPin =  -1, int rxPin = -1, int baud = 115200);
	void poll();
	bool hasRx() const { return m_hasRx; }
	int get(uint8_t *d);
	std::vector<uint8_t> get();
	bool put(const  uint8_t *d, size_t l);
	bool put(std::vector<uint8_t> d);

protected:
	static constexpr int MaxLen = 100;
	uint8_t m_rxbuffer[MaxLen+1];
	int m_rxLen;
	void uartIsr() override;
private:
	void clearRx();
	bool m_waitAck;
	uint8_t m_respRxd;
	uint8_t m_respTx;
	uint8_t m_rxCrc;
	bool m_hasRx;
	void put(uint8_t c) { uart_putc_raw(m_uart, char(c)); }
	void (UartIpc::*m_rxState)(uint8_t rxd);
	// state fcts
	absolute_time_t m_txTime;
public:
	void rxIdle(uint8_t c);
	void rxData(uint8_t c);
	void rxDle(uint8_t c);
	void rxCrc(uint8_t c);
	void addRxData(uint8_t c);

//	bool timer_callback(repeating_timer_t *rt);
};

#endif // UARTIPC_H
