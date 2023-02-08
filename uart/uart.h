// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/8/2023 by behm
// ******************************************************

#ifndef UART_H
#define UART_H

#include "pico/stdlib.h"
#include "pico/util/queue.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

class Uart
{
public:
	Uart(int uartIdx, int txPin =  -1, int rxPin = -1, int baud = 115200);
	bool hasrx();
	uint8_t get();
	bool canTx();
	bool put(uint8_t c);
	bool put(char c) { return put(uint8_t(c)); }
	void put(const char *s);
	void put(const uint8_t *s, size_t n) ;
	int baud() const { return m_baud; }
	void setBaud(int baud);
	int txPin() const { return m_txPin; }
	int rxPin() const { return m_rxPin; }
	int uartIdx() const { return m_uartIdx; }

protected:
	static constexpr int qsize = 100;
	const int m_txPin;
	const int m_rxPin;
	int m_baud;
	const int m_uartIdx;
	uart_inst_t * const m_uart;
	// need to have the following to be static, sinec we don't get any instance info into the isr
	struct UartDefine
	{
		int8_t txPin, rxPin;
		uint irq;
		Uart *uart;
		void (*rxisr)();
	};
	static UartDefine uartDefinition[2];
	static int getTxPin(int idx, int tx);
	static int getRxPin(int idx, int rx);
	queue_t m_rxq;
//	queue_t m_txq;
	void uartIsr();
	static void uart0Isr();
	static void uart1Isr();
};

#endif // UART_H
