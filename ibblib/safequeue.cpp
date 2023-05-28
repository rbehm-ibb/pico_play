 ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 3/27/2023 by behm
// ******************************************************

#include "safequeue.h"

//template<class T> SafeQueue<T>::SafeQueue(size_t size) : m_size(size) , m_head(0), m_tail(0) { m_data =  new T[m_size]; }

//template<class T> SafeQueue<T>::~SafeQueue()
//{
//	delete m_data;
//	m_data = nullptr;
//}

template<class T> bool SafeQueue<T>::put(T d)
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

template<class T> bool SafeQueue<T>::get(T &d)
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

template<class T> bool SafeQueue<T>::isEmpty() const
{
	return (m_tail == m_head);
}

//std::ostream &operator<<(std::ostream &s, const  SafeQueue &q)
//{
//	return s << q.m_head << ':' << q.m_tail << ' ';
//}

