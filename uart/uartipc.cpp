// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/9/2023 by behm
// ******************************************************

#include "uartipc.h"

UartIpc::UartIpc(int uartIdx, int txPin, int rxPin, int baud)
	: Uart(uartIdx, txPin, rxPin, baud)
{

}


void UartIpc::uartIsr()
{
}
