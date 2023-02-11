// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/8/2023 by behm
// ******************************************************

#ifndef UARTBASE_H
#define UARTBASE_H

#include "hardware/uart.h"

///
/// \brief The Uart class is only a virtual base class for all Uart classes.
/// It handles basic setup and interrupt handling and call a virtual function to do the real wokd.
///
class UartBase
{
public:
	UartBase(int uartIdx, int txPin =  -1, int rxPin = -1, int baud = 115200);
	virtual ~UartBase();
	int baud() const { return m_baud; }
	void setBaud(int baud);
	int txPin() const { return m_txPin; }
	int rxPin() const { return m_rxPin; }
	int uartIdx() const { return m_uartIdx; }

protected:
	const int m_txPin;
	const int m_rxPin;
	int m_baud;
	const int m_uartIdx;
	uart_inst_t * const m_uart;
	// need to have the following to be static, sinec we don't get any instance info into the isr
	struct UartDescr
	{
		int8_t txPin, rxPin;
		uint16_t irq;
		UartBase *uart;
		void (*rxisr)();
	};
	UartDescr *m_descr;
	static UartDescr uartDefinition[2];
	static int getTxPin(int idx, int tx);
	static int getRxPin(int idx, int rx);
	virtual void uartIsr() = 0;
	static void uart0Isr();
	static void uart1Isr();
	void put(char c) { uart_putc_raw(m_uart, c); }
	void put(uint8_t c) { put(char(c)); }
};

#endif // UARTBASE_H
