// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/8/2023 by behm
// ******************************************************

#include <iostream>
#include "uart.h"

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
	invalid_params_if(UART, uartIdx != 0 && uartIdx != 1);
	if (uartIdx != 0 && uartIdx != 1)
	{
		std::cerr << __PRETTY_FUNCTION__ << " bad Uart#" << uartIdx << std::endl;
	}
	UartDefine &uartDef = uartDefinition[uartIdx];
	uartDef.uart = this;
	uart_init(m_uart, m_baud);
	gpio_set_function(m_txPin, GPIO_FUNC_UART);
	gpio_set_function(m_rxPin, GPIO_FUNC_UART);
	uart_set_hw_flow(m_uart, false, false);
	uart_set_format(m_uart, 8, 2, UART_PARITY_NONE);
	uart_set_fifo_enabled(m_uart, true);
	while (uart_is_readable_within_us(m_uart, 100))
	{
		uart_getc(m_uart);
	}
	irq_set_exclusive_handler(uartDef.irq, uartDef.rxisr);
	irq_set_enabled(uartDef.irq, true);
	uart_set_irq_enables(m_uart, true, false);
}

void Uart::setBaud(int baud)
{
	m_baud = baud;
	uart_set_baudrate(m_uart, m_baud);
}

void Uart::uart0Isr()
{
	uartDefinition[0].uart->uartIsr();
}

void Uart::uart1Isr()
{
	uartDefinition[1].uart->uartIsr();
}
