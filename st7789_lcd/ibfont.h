// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/30/2022 by behm
// ******************************************************

#ifndef IBFONT_H
#define IBFONT_H

#include <stdint.h>
#include "point.h"

class IbFont
{
public:
	IbFont(uint8_t w, uint8_t h, char first, bool reverse, const uint8_t *bytes)
		: m_pixc(w*h)
		, m_w(w), m_h(h)
		, m_bpc(w*h/8)
		, m_first(first)
		, m_reverse(reverse)
		, m_bytes(bytes)
		{}
//	Rect charRect(const Point &p) const { return Rect(p, Size(m_w, m_h)); }
	Size charSize() const { return Size(m_w, m_h); }
	char first() const { return m_first; }

	const uint8_t *charBytes(char c) const { return m_bytes + (c - m_first) * m_bpc; }
	uint16_t pixc() const { return m_pixc; }
	uint8_t h() const { return m_h; }
	uint8_t w() const { return m_w; }

	bool reverse() const { return m_reverse; }

protected:
	/// pixel count per char
	const uint16_t m_pixc;
	/// char width
	const uint8_t m_w;
	/// char height
	const uint8_t m_h;
	/// byte/char = m_w*m_h/8
	const uint8_t m_bpc;
	/// the first char
	const char m_first;
	/// are the bit reversed?
	const bool m_reverse;
	/// the pixmaps
	const uint8_t * const m_bytes;
};

#endif // IBFONT_H
