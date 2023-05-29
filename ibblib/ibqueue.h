// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 5/29/2023 by behm
// ******************************************************

#ifndef IBQUEUE_H
#define IBQUEUE_H

//#include <stdio.h>
#include <atomic>
#include <stdint.h>

void Qtest();

template <typename T> class IbQueue
{
public:
	IbQueue(uint16_t size) : m_data(new T[size]), m_size(size) { clear(); }
	~IbQueue() { delete m_data; }
	bool ok() const { return m_data !=  nullptr; }
	bool put(T d);
	bool get(T &d);
	bool isEmpty() const;
	bool isFull() const;
	void clear() { m_head = 0; m_tail = 0; }
private:
	T *m_data;
	const uint16_t m_size;
	volatile std::atomic_uint_fast16_t m_head;
	volatile std::atomic_uint_fast16_t m_tail;
};

template<typename T> bool IbQueue<T>::put(T d)
{
	uint16_t newhead = m_head + 1;
	if (newhead >= m_size)
	{
		newhead = 0;
	}
	if (newhead !=  m_tail)
	{
		m_data[m_head] = d;
		m_head =  newhead;
		return true;
	}
	return false;
}

template<typename T> bool IbQueue<T>::get(T &d)
{
	if (m_tail != m_head)
	{
		d = m_data[m_tail];
		uint16_t nt = m_tail + 1;
		if (nt >= m_size)
		{
			nt = 0;
		}
		m_tail = nt;
		return true;
	}
	return false;
}

template<typename T> bool IbQueue<T>::isEmpty() const
{
	return (m_tail == m_head);
}

template<typename T> bool IbQueue<T>::isFull() const
{
	uint16_t newhead = m_head + 1;
	if (newhead >= m_size)
	{
		newhead = 0;
	}
	return (newhead == m_tail);
}

#endif // IBQUEUE_H
