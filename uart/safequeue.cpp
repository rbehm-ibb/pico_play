// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 3/27/2023 by behm
// ******************************************************

#include "safequeue.h"

SafeQueue::SafeQueue(uint16_t size)
	: m_size(size)
	, m_head(0)
	, m_tail(0)
{
	m_data =  new uint8_t[m_size];
}

SafeQueue::~SafeQueue()
{
	delete m_data;
	m_data = nullptr;
}

bool SafeQueue::put(uint8_t d)
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

bool SafeQueue::get(uint8_t &d)
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

bool SafeQueue::isEmpty() const
{
	return (m_tail != m_head);
}
