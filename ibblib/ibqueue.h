// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@becker.com.tw
// * All Rights reserved
// * created 5/29/2023 by behm
// ******************************************************

#ifndef IBQUEUE_H
#define IBQUEUE_H

#include <atomic>
#include <stdint.h>

///
/// \brief The IbQueue class is a safe replacement for the SDK queue_t.
///
/// It implements only minimal functionality to allow it to work without locking.
/// The SDK queue uses locking with a spinlock. This has the risk of priority inversion when used from on ISR
/// because it would stall forever when the foreground had aquired the spinlock.
///
/// The template type must be a POD.
///
///
template <typename T, int N> class IbQueue
{
public:
	///
	/// \brief IbQueue create a queue for N elements of type T
	/// \param size number of elements for the queue
	///
	IbQueue() : m_data(new T[N]) { clear(); }
	///
	/// \brief ~IbQueue relase  all heap data
	~IbQueue() { delete m_data; }
	///
	/// \brief ok test if creation was ok
	/// \return instance is usable
	///
	bool ok() const { return m_data !=  nullptr; }
	///
	/// \brief put a new item into the Q if possible
	/// \param d [in] data to put
	/// \return true if success, else nothing done
	///
	bool put(T d);
	///
	/// \brief get try to get an item from the Q, if was empty nothing is done
	/// \param d [out] the fetched item
	/// \return true if there was something, else d is not changed
	///
	bool get(T &d);
	///
	/// \brief isEmpty is the Q empty?
	/// \return is empty
	///
	bool isEmpty() const;
	///
	/// \brief isFull is the Q full?
	/// \return is full
	///
	bool isFull() const;
	///
	/// \brief clear the Q
	///
	void clear() { m_head = 0; m_tail = 0; }
private:
	T *m_data;	///< space for the items
//	static constexpr uint_fast8_t m_size = N;	///< max number of items
	volatile std::atomic_uint_fast8_t m_head;	///< index to  next  free item
	volatile std::atomic_uint_fast8_t m_tail;	///< index to oldest item
};

template<typename T, int N> bool IbQueue<T,N>::put(T d)
{
	uint16_t newhead = m_head + 1;
	if (newhead >= N)
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

template<typename T, int N> bool IbQueue<T,N>::get(T &d)
{
	if (m_tail != m_head)
	{
		d = m_data[m_tail];
		uint16_t nt = m_tail + 1;
		if (nt >= N)
		{
			nt = 0;
		}
		m_tail = nt;
		return true;
	}
	return false;
}

template<typename T, int N> bool IbQueue<T,N>::isEmpty() const
{
	return (m_tail == m_head);
}

template<typename T, int N> bool IbQueue<T,N>::isFull() const
{
	uint16_t newhead = m_head + 1;
	if (newhead >= N)
	{
		newhead = 0;
	}
	return (newhead == m_tail);
}

#endif // IBQUEUE_H
