// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/9/2023 by behm
// ******************************************************

//#include <iostream>
#include <string.h>
#include "uartline.h"

using namespace std;

UartLine::UartLine(int uartIdx, int txPin, int rxPin, int baud)
	: Uart(uartIdx, txPin, rxPin, baud)
{
	setLeadin("$");
	setLeadout("\n");
	setIgnore('\r');
	clearLine();
}

bool UartLine::getLine(char *s)
{
	if (m_hasLine)
	{
		strcpy(s, m_line);
		clearLine();
		return true;
	}
	return false;
}

void UartLine::putLine(const char *s)
{
	put(leadin());
	put(s);
	put(leadout());
}

void UartLine::put(const char *s)
{
	while (*s)
	{
		uart_putc_raw(m_uart, *s++);
	}
}

void UartLine::clearLine()
{
	m_hasLine = false;
	m_hadLeadin = false;
	memset(m_line, 0, sizeof(m_line));
	m_lineLen = 0;
	m_inMatch.reset();
	m_outMatch.reset();
}

void UartLine::uartIsr()
{
	while (uart_is_readable(m_uart))
	{
		charRxd(uart_getc(m_uart));
	}
}

//  process rxd char
void UartLine::charRxd(char c)
{
	if (c == m_ignore)
	{
		return;
	}
	if (m_hasLine)
	{
		return;		// we are busy
	}
	if (m_hadLeadin)
	{
		if (m_outMatch.tryMatch(c))
		{
			m_lineLen -= m_outMatch.idx() - 1;
			m_line[m_lineLen] = '\0';
			m_hasLine = true;
			return;
		}
		if (m_lineLen < maxLineLength)
		{
			m_line[m_lineLen++] = c;
		}
		// else overflow, just ignore
		return;
	}
	if (m_inMatch.tryMatch(c))
	{
		clearLine();
		m_hadLeadin  = true;
	}
}

Matcher::Matcher()
{
	setMatch("");
	reset();
}

bool Matcher::tryMatch(char c)
{
	if (c == m_match[m_idx])
	{
		++m_idx;
		return m_match[m_idx] == '\0';
	}
	m_idx = 0;
	return false;
}

void Matcher::setMatch(const char *s)
{
	memset(m_match, 0, sizeof(m_match));
	strncpy(m_match, s, maxSeq);
}


