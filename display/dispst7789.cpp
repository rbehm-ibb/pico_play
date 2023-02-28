// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/27/2023 by behm
// ******************************************************

#include "dispst7789.h"

static constexpr uint8_t CMD_PORCTRL  = 0xB2;      // Porch control
static constexpr uint8_t CMD_GCTRL    = 0xB7;      // Gate control
static constexpr uint8_t CMD_VCOMS    = 0xBB;      // VCOMS setting
static constexpr uint8_t CMD_LCMCTRL  = 0xC0;      // LCM control
static constexpr uint8_t CMD_VDVVRHEN = 0xC2;      // VDV and VRH command enable
static constexpr uint8_t CMD_VRHS     = 0xC3;      // VRH set
static constexpr uint8_t CMD_VDVSET   = 0xC4;      // VDV setting
static constexpr uint8_t CMD_FRCTR2   = 0xC6;      // FR Control 2
static constexpr uint8_t CMD_PWCTRL1  = 0xD0;      // Power control 1
static constexpr uint8_t CMD_PVGAMCTRL= 0xE0;      // Positive voltage gamma control
static constexpr uint8_t CMD_NVGAMCTRL= 0xE1;      // Negative voltage gamma control
static constexpr uint8_t CMD_SLPOUT  = 0xAF;
static constexpr uint8_t CMD_IDMOFF  = 0x38;
static constexpr uint8_t CMD_DISPON  = 0xA5;
static constexpr uint8_t CMD_INIT_DELAY = 0x80;

// format cmd, delay/count, parms[count]
static const uint8_t initList[] =
{
	CMD_PORCTRL, 5, 0x0c, 0x0c, 0x00, 0x33, 0x33,
	CMD_GCTRL  , 1, 0x35,

	CMD_VCOMS  , 1, 0x28,  // JLX240 display datasheet
	CMD_LCMCTRL, 1, 0x0C,
	CMD_VDVVRHEN,2, 0x01, 0xFF,
	CMD_VRHS   , 1, 0x10,      // voltage VRHS
	CMD_VDVSET , 1, 0x20,
	CMD_FRCTR2 , 1, 0x0f,      // 0x0f=60Hz
	CMD_PWCTRL1, 2, 0xa4, 0xa1,
	//--------------------------------ST7789V gamma setting---------------------------------------//
	CMD_PVGAMCTRL,14, 0xd0,0x00,0x02,0x07,
			   0x0a,0x28,0x32,0x44,
			   0x42,0x06,0x0e,0x12,
			   0x14,0x17,
	CMD_NVGAMCTRL,14, 0xd0,0x00,0x02,0x07,
			   0x0a,0x28,0x31,0x54,
			   0x47,0x0e,0x1c,0x17,
			   0x1b,0x1e,
	CMD_SLPOUT, 0+CMD_INIT_DELAY, 130,    // Exit sleep mode
	CMD_IDMOFF, 0,
	CMD_DISPON, 0,
	0xFF,0xFF, // end

};

DispSt7789::DispSt7789(SpiBase * const ioChannel, const IbSize &size)
	: DisplayBase(ioChannel, size)
{

}

void DispSt7789::init()
{
	sendInitSeq(initList);
}

void DispSt7789::drawPoint(const IbPoint p)
{
}

void DispSt7789::fillRect(const IbRect &r)
{
}

void DispSt7789::setRect(const IbRect &newRect)
{
}


void DispSt7789::drawHLine(const IbPoint p, coord_t w)
{
}

void DispSt7789::drawVLine(const IbPoint p, coord_t h)
{
}

IbPoint DispSt7789::drawChar(const IbPoint p, char c)
{
}
