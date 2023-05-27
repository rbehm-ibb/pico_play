// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 5/18/2023 by behm
// ******************************************************

#ifndef PIOUTIL_H
#define PIOUTIL_H

#include <iostream>
#include "hardware/pio.h"

std::ostream &operator<<(std::ostream &s, const pio_sm_config &p);
static inline int bits(uint32_t reg, int lsb, uint32_t mask) { return (reg & mask) >> lsb; }
class PioUtil
{
	friend std::ostream &operator<<(std::ostream &s, const PioUtil &p);
public:
	enum Dir { In = 0, Out };
	struct PinDef
	{
		int pin;
		Dir dir;
	};
	PioUtil(PIO pio, int smIdx);
	void setPgm(const pio_program_t pgm);
	void setSmConf(const pio_sm_config &newSmConf);
	void putSmConfig();
	void enable();
	void disable();
	void setBaud(uint baud);
	void setPins(const PinDef *pindef);
	void setOutPins(int base, int count);
	void setSetPins(int base, int count);
	void setInPins(int base);
	void setSidePins(int base);
	void setJmpPin(int pin);
	void setOutShift(bool shift_right, bool autopull, uint pull_threshold);
	void setInShift(bool shift_right, bool autopush, uint push_threshold);
//	pio_sm_config &smConf() { return m_smConf; }
	uint offset() const { return m_offset; }

private:
	const PIO m_pio;
	const int m_idx;
	pio_sm_config m_smConf;
	pio_program_t m_pgm;
	uint m_offset;
	int pinbits(int lsb, uint32_t mask) const;
};

#endif // PIOUTIL_H
