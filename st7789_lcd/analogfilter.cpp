// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 7/16/2023 by behm
// ******************************************************

#include "analogfilter.h"

AnalogFilter::AnalogFilter(int len)
	: m_count(0)
	, m_length(len)
	, m_dir(None)
{
}

float AnalogFilter::add(const float v)
{
	switch (m_dir)
	{
	case None:
		if (v > m_value)
		{
			m_dir = Up;
			++m_count;
		}
		else if (v < m_value)
		{
			m_dir = Down;
			++m_count;
		}
		break;
	case Up:
		if (v >= m_value)
		{
			if (m_count >= m_length)
			{
				m_value = (m_value +v) / 2.0;
			}
			else
			{
				++m_count;
			}
		}
		else
		{
			m_dir = None;
			m_count = 0;
		}
		break;
	case Down:
		if (v <= m_value)
		{
			if (m_count >= m_length)
			{
				m_value = (m_value +v) / 2.0;
			}
			else
			{
				++m_count;
			}
		}
		else
		{
			m_dir = None;
			m_count = 0;
		}
		break;
	}
	return m_value;
}
