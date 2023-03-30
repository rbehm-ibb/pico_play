// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/9/2023 by behm
// ******************************************************

#ifndef UARTIPC_H
#define UARTIPC_H

#include <vector>
#include "pico/util/queue.h"
#include "uartbase.h"

class UartIpc : public UartBase
{
public:
	enum Ctrl { STX='S', ETX='E', DLE='D', ACK='A', NAK='N', ENQ='Q', WACK='W', ENQNAK = 'k' };
	UartIpc(int uartIdx, int txPin =  -1, int rxPin = -1, int baud = 115200);
	void poll();
	bool hasRx() const { return m_hasRx; }
	std::vector<uint8_t> get();
	bool put(const  uint8_t *d, size_t l);
	bool put(std::vector<uint8_t> d);

protected:
	void uartIsr() override;
private:
	void clearRx();
	bool m_waitAck;
	uint8_t m_respRxd;
	uint8_t m_respTx;
	uint8_t m_rxCrc;
	uint8_t m_hadCrc;
	int m_repeat;
	bool m_hasRx;

	static constexpr int MaxLen = 100;
	std::vector<uint8_t> m_rxbuffer;
	std::vector<uint8_t> m_txbuffer;
	void (UartIpc::*m_rxState)(uint8_t rxd);
	// state fcts
	absolute_time_t m_txTime;
	void rxIdle(uint8_t c);
	void rxData(uint8_t c);
	void rxDle(uint8_t c);
	void rxCrc(uint8_t c);
	void addRxData(uint8_t c);

//	bool timer_callback(repeating_timer_t *rt);
	struct States
	{
		const char *name;
		void (UartIpc::*state)(uint8_t rxd);
	};
	static States states[5];

};

#endif // UARTIPC_H
