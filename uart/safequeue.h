// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 3/27/2023 by behm
// ******************************************************

#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H

#include <iostream>
#include <atomic>
#include <stdint.h>

///
/// \brief The SafeQueue class is a queue that is safe to be called from interrupt
///
/// The SDK queue type is not safe against priority inversion, because it uses a spin lock.
/// If the fg process  holds the spinlock and ISR wil have to wait forever.
/// This form of a queue is inherently safe against concurrent accesss w/o and locking.
/// Usage from different cores has to be checked.
///
class SafeQueue
{
	friend std::ostream &operator<<(std::ostream &s, const  SafeQueue &q);
public:
	SafeQueue(uint16_t size);
	~SafeQueue();
	bool ok() const { return m_data !=  nullptr; }
	bool put(uint8_t d);
	bool get(uint8_t &d);
	bool isEmpty() const;
protected:
	const uint16_t m_size;
	volatile std::atomic<uint16_t> m_head;
	volatile std::atomic<uint16_t> m_tail;
	uint8_t *m_data;
};

#endif // SAFEQUEUE_H
