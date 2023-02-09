// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/9/2023 by behm
// ******************************************************

#ifndef UARTIPC_H
#define UARTIPC_H

#include "uart.h"

class UartIpc : public Uart
{
public:
	UartIpc(int uartIdx, int txPin =  -1, int rxPin = -1, int baud = 115200);

	// Uart interface
protected:
	void uartIsr() override;
	bool timer_callback(repeating_timer_t *rt);
};

#endif // UARTIPC_H
