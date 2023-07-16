// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 7/16/2023 by behm
// ******************************************************

#ifndef ANALOGFILTER_H
#define ANALOGFILTER_H


class AnalogFilter
{
public:
	AnalogFilter(int len);
	float add(const float v);
private:
	float m_value;
	int m_count;
	const int m_length;
	enum Dir { None, Up, Down };
	Dir m_dir;
};

#endif // ANALOGFILTER_H
