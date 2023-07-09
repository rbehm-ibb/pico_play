// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 6/2/2023 by behm
// ******************************************************

#ifndef BLINK_H
#define BLINK_H

#include "xtask.h"

class Blink : public Task
{
public:
	Blink(int pin);
protected:
	void proc() override;
	const char *name() const;
private:
	int m_pin;
	char *xname(int pin);
	char m_name[20];
};

#endif // BLINK_H
