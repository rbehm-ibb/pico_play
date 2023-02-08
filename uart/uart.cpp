// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/8/2023 by behm
// ******************************************************

#include <iostream>
#include "uart.h"

//#define USE_TXISR

Uart::UartDefine Uart::uartDefinition[] =
{
	{  0,  1, UART0_IRQ, nullptr, &Uart::uart0Isr },
	{ 20, 21, UART1_IRQ, nullptr, &Uart::uart1Isr }
};
inline int Uart::getTxPin(int idx, int tx)
{
	if (tx >= 0)
		return tx;
	assert(idx = 0 || idx == 1);
	return Uart::uartDefinition[idx].txPin;
}
inline int Uart::getRxPin(int idx, int rx)
{
	if (rx >= 0)
		return rx;
	assert(idx = 0 || idx == 1);
	return Uart::uartDefinition[idx].rxPin;
}

Uart::Uart(int uartIdx, int txPin, int rxPin, int baud)
	: m_txPin(getTxPin(uartIdx, txPin))
	, m_rxPin(getRxPin(uartIdx, rxPin))
	, m_baud(baud)
	, m_uartIdx(uartIdx)
	, m_uart(uart_get_instance(uartIdx))
{
	assert(uartIdx = 0 || uartIdx == 1);
	UartDefine &uartDef = uartDefinition[uartIdx];
	uartDef.uart = this;
	queue_init(&m_rxq, sizeof(uint8_t), qsize);
#ifdef USE_TXISR
	queue_init(&m_txq, sizeof(uint8_t), qsize);
#endif
	uart_init(m_uart, m_baud);
	gpio_set_function(m_txPin, GPIO_FUNC_UART);
	gpio_set_function(m_rxPin, GPIO_FUNC_UART);
	uart_set_hw_flow(m_uart, false, false);
	uart_set_format(m_uart, 8, 2, UART_PARITY_NONE);
	uart_set_fifo_enabled(m_uart, false);
	while (uart_is_readable_within_us(m_uart, 100))
	{
		uart_getc(m_uart);
	}
	irq_set_exclusive_handler(uartDef.irq, uartDef.rxisr);
	irq_set_enabled(uartDef.irq, true);
	uart_set_irq_enables(m_uart, true, false);
}

bool Uart::hasrx()
{
	return ! queue_is_empty(&m_rxq);
}

uint8_t Uart::get()
{
	uint8_t c;
	queue_remove_blocking(&m_rxq, &c);
	return c;
}

bool Uart::canTx()
{
#ifdef USE_TXISR
	return ! queue_is_full(&m_txq);
#else
	return uart_is_writable(m_uart);
#endif
}

bool Uart::put(uint8_t c)
{
#ifdef USE_TXISR
	if (queue_try_add(&m_txq, &c))
	{
		// need  to (re-)start tx interr.
		return true;
	}
	return false;
#else
	if (canTx())
	{
//		std::cout << __PRETTY_FUNCTION__  << "[" << c << "]" << std::endl;
		uart_putc(m_uart, char(c));
		return true;
	}
	return false;
#endif
}

void Uart::put(const char *s)
{
//	std::cout << __PRETTY_FUNCTION__ << "<" << s << ">" << std::endl;
	while (*s)
	{
		do {}
		while (! put(*s));
		++s;
	}
}

void Uart::put(const uint8_t *s, size_t n)
{
	while (n)
	{
		do {}
		while (! put(*s));
		++s;
		--n;
	}
}

void Uart::setBaud(int baud)
{
	m_baud = baud;
	uart_set_baudrate(m_uart, m_baud);
}

void Uart::uartIsr()
{
	while (uart_is_readable(m_uart))
	{
		uint8_t ch = uart_getc(m_uart);
		queue_add_blocking(&m_rxq, &ch);
	}
#ifdef USE_TXISR
	// need to handle tx interr.
#endif
}

void Uart::uart0Isr()
{
	uartDefinition[0].uart->uartIsr();
}

void Uart::uart1Isr()
{
	uartDefinition[1].uart->uartIsr();
}
