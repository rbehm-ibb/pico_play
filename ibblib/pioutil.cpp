// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 5/18/2023 by behm
// ******************************************************

#include "pioutil.h"
#include "hardware/clocks.h"
#include "hardware/structs/clocks.h"

PioUtil::PioUtil(PIO pio, int smIdx)
	: m_pio(pio)
	, m_idx(smIdx)
{
}

void PioUtil::setPgm(const pio_program_t pgm)
{
	m_pgm =  pgm;
	m_offset = pio_add_program(m_pio, &m_pgm);
}

void PioUtil::enable()
{
	pio_sm_set_enabled(m_pio, m_idx, true);
}

void PioUtil::disable()
{
	pio_sm_set_enabled(m_pio, m_idx, false);
}

void PioUtil::setBaud(uint baud)
{
	float sysClock = clock_get_hz(clk_sys);
	float clkdiv = sysClock / baud;
	sm_config_set_clkdiv(&m_smConf, clkdiv);   // 4. Set clock divider
}

void PioUtil::setPins(const PinDef *pindef)
{
	for ( ; pindef->pin >= 0; ++pindef)
	{
		pio_gpio_init(m_pio, pindef->pin);
		pio_sm_set_consecutive_pindirs(m_pio, m_idx, pindef->pin, 1, pindef->dir == Out);
	}
}

void PioUtil::setOutPins(int base, int count)
{

	sm_config_set_out_pins(&m_smConf, base, count);
//	std::cout << __PRETTY_FUNCTION__ << " " << base << "." << count << ":" << std::hex << m_smConf.pinctrl << std::dec << std::endl;
}

void PioUtil::setSetPins(int base, int count)
{
	sm_config_set_set_pins(&m_smConf, base, count);
//	std::cout << __PRETTY_FUNCTION__ << " " << base << "." << count << ":" << std::hex << m_smConf.pinctrl << std::dec << std::endl;
}

void PioUtil::setInPins(int base)
{
	sm_config_set_in_pins(&m_smConf, base);
//	std::cout << __PRETTY_FUNCTION__ << " " << base << ":" << std::hex << m_smConf.pinctrl << std::dec << std::endl;
}

void PioUtil::setSidePins(int base)
{
	sm_config_set_sideset_pins(&m_smConf, base);
//	std::cout << __PRETTY_FUNCTION__ << " " << base << ":" << std::hex << m_smConf.pinctrl
//		  << "!" << PIO_SM0_PINCTRL_SIDESET_BASE_LSB << "$" << PIO_SM0_PINCTRL_SIDESET_BASE_BITS << std::dec << std::endl;
}

void PioUtil::setJmpPin(int pin)
{
	sm_config_set_jmp_pin(&m_smConf, pin);
//	std::cout << __PRETTY_FUNCTION__ << " " << pin << ":" << std::hex << m_smConf.pinctrl << std::dec << std::endl;
}

void PioUtil::setOutShift(bool shift_right, bool autopull, uint pull_threshold)
{
	sm_config_set_out_shift(&m_smConf, shift_right, autopull, pull_threshold);
}

void PioUtil::setInShift(bool shift_right, bool autopush, uint push_threshold)
{
	sm_config_set_in_shift(&m_smConf, shift_right, autopush, push_threshold);
}



void PioUtil::setSmConf(const pio_sm_config &newSmConf)
{
	m_smConf = newSmConf;
}

void PioUtil::putSmConfig()
{
	pio_sm_init(m_pio, m_idx, m_offset, &m_smConf);
}

int PioUtil::pinbits(int lsb, uint32_t mask) const
{
	return (m_smConf.pinctrl & mask) >> lsb;
}

std::ostream &operator<<(std::ostream &s, const PioUtil &p)
{
	return s << "Pio:" << pio_get_index(p.m_pio) << " SM:" << p.m_idx
		 << " Offset=" << p.m_offset << " PgmL=" << int(p.m_pgm.length)
		 << p.m_smConf;
}

std::ostream &operator<<(std::ostream &s, const pio_sm_config &p)
{
	uint16_t clkdiv = bits(p.clkdiv, PIO_SM0_CLKDIV_INT_LSB, PIO_SM0_CLKDIV_INT_BITS);
	uint16_t clkfrac = bits(p.clkdiv, PIO_SM0_CLKDIV_FRAC_LSB, PIO_SM0_CLKDIV_FRAC_BITS);
	uint32_t sysClock = clock_get_hz(clk_sys);
	s << " clkdiv=" << clkdiv << " clkfrac=" << clkfrac << " sys=" << sysClock*1e-6 << "MHz q=" << sysClock/clkdiv << "Hz" << std::endl;
	s << std::hex
	  << " clk:" << p.clkdiv << " shift:" << p.shiftctrl << " pin:" << p.pinctrl << " exec:" << p.execctrl << std::dec << std::endl
	  << " In  : " << bits(p.pinctrl, PIO_SM0_PINCTRL_IN_BASE_LSB, PIO_SM0_PINCTRL_IN_BASE_BITS) << std::endl
	  << " Out : " << bits(p.pinctrl, PIO_SM0_PINCTRL_OUT_BASE_LSB, PIO_SM0_PINCTRL_OUT_BASE_BITS) << "#" << bits(p.pinctrl, PIO_SM0_PINCTRL_OUT_COUNT_LSB, PIO_SM0_PINCTRL_OUT_COUNT_BITS) << std::endl
	  << " Set : " << bits(p.pinctrl, PIO_SM0_PINCTRL_SET_BASE_LSB, PIO_SM0_PINCTRL_SET_BASE_BITS) << "#" << bits(p.pinctrl, PIO_SM0_PINCTRL_SET_COUNT_LSB, PIO_SM0_PINCTRL_SET_COUNT_BITS) << std::endl
	  << " Side: " << bits(p.pinctrl, PIO_SM0_PINCTRL_SIDESET_BASE_LSB, PIO_SM0_PINCTRL_SIDESET_BASE_BITS) << std::endl
	  << " Jmp : " << bits(p.execctrl, PIO_SM0_EXECCTRL_JMP_PIN_LSB, PIO_SM0_EXECCTRL_JMP_PIN_BITS) << std::endl
	  << "OShft: " << (bits(p.shiftctrl, PIO_SM0_SHIFTCTRL_OUT_SHIFTDIR_LSB, 0x01) ? "right " : "left ")
	  << (bits(p.shiftctrl, PIO_SM0_SHIFTCTRL_AUTOPULL_LSB, 0x01) ? "autop " : "noautop ")
	  << (bits(p.shiftctrl, PIO_SM0_SHIFTCTRL_PULL_THRESH_LSB, PIO_SM0_SHIFTCTRL_PULL_THRESH_BITS))	<< "bits" << std::endl
	  << "IShft: " << (bits(p.shiftctrl, PIO_SM0_SHIFTCTRL_IN_SHIFTDIR_LSB, 0x01) ? "right " : "left ")
	  << (bits(p.shiftctrl, PIO_SM0_SHIFTCTRL_AUTOPULL_LSB, 0x01) ? "autop " : "noautop ")
	  << (bits(p.shiftctrl, PIO_SM0_SHIFTCTRL_PUSH_THRESH_LSB, PIO_SM0_SHIFTCTRL_PUSH_THRESH_BITS))	<< "bits" << std::endl
	  ;
	return s;

}
