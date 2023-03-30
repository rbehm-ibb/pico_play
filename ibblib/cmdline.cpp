// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/7/2023 by behm
// ******************************************************

#include <iostream>
#include <string.h>
#include "pico/stdio.h"
#include "cmdline.h"

CmdLine::CmdLine(const Cmd * const cmds, const char *dlm)
	: m_cmds(cmds)
	, m_dlm(dlm)
{
	clear();
}

void CmdLine::clear()
{
	m_linelen = 0;
	memset(m_line, 0, sizeof(m_line));
	m_args.clear();
}

void CmdLine::evalLine()
{
	m_args.clear();
	for (char *t = strtok(m_line, m_dlm); t; t = strtok(nullptr, m_dlm))
	{
		m_args.push_back(t);
	}
	if (m_args.empty())
	{
		return;
	}
	const char *cmd = m_args.front();
	for (const Cmd *p = m_cmds; p->cmd; ++p)
	{
		if (strcmp(cmd, p->cmd) == 0)
		{
			(*p->callback)(m_args);
			return;
		}
	}
	std::cout << "?? <" << cmd << ">" << std::endl;
}

void CmdLine::poll()
{
	const int c = getchar_timeout_us(0);
	if (c < 0)
		return;
	switch (c)
	{
	case '\b':
		if (m_linelen > 0)
		{
			--m_linelen;
			m_line[m_linelen] = '\0';
		}
		break;
	case 0x1b:	// ESC
	case 0x03:	// ^C
		clear();
		break;
	case '\r':
	case '\n':
		std::cout << std::endl;
		evalLine();
		clear();
		return;
	default:
		if (c < ' ')
		{
			break;
		}
		if (m_linelen < maxline)
		{
			m_line[m_linelen++] = c;
		}
	}
	return;
}


std::ostream &operator<<(std::ostream &s, const CmdLine::Args &d)
{
	for (const char *sd : d)
	{
		s << " <" << sd << ">";
	}
	return s;
}

const char *CmdLine::Args::argn(uint n) const
{
	if (n < size()) return at(n);
	return nullptr;
}

int CmdLine::Args::num(int n, uint base) const
{
	return strtol(argn(n), nullptr, base);
}

std::vector<uint8_t> CmdLine::Args::asVecu8(int n) const
{
	std::vector<uint8_t> res;
	if (n < size())
	{
		const char *s = at(n);
		const int l = strlen(s);
		res.reserve(l);
		for (int i = 0; i < l; ++i)
		{
			res.push_back(s[i]);
		}
	}
	return res;
}
