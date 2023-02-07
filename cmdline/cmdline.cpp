// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/7/2023 by behm
// ******************************************************

#include <string.h>
#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
#include "pico/stdlib.h"
#include "cmdline.h"

using namespace std;


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

const char *CmdLine::argn(uint n) const
{
	if (n < m_args.size()) return m_args.at(n);
	return nullptr;
}

int CmdLine::num(uint n, uint base) const
{
	return strtol(argn(n), nullptr, base);
}

void CmdLine::evalLine()
{
	//	cout << __PRETTY_FUNCTION__ << "<" << m_line << ">" << endl;
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
}

int CmdLine::poll()
{
	const int c = getchar_timeout_us(0);
	if (c < 0)
		return NoIn;
//	cout << hex << c << dec << ": -->";
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
		cout << endl;
		evalLine();
		clear();
		return 0;
		break;
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
//	cout << "<" << m_line << ">" << endl;
	return NoIn;
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
