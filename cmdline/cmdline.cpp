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

CmdLine::CmdLine(const Cmd *const cmds)
	: m_cmds(cmds)
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

int CmdLine::evalLine()
{
	//	cout << __PRETTY_FUNCTION__ << "<" << m_line << ">" << endl;
	m_args.clear();
	for (char *t = strtok(m_line, " "); t; t = strtok(nullptr, " "))
	{
		m_args.push_back(t);
	}
	if (m_args.empty())
	{
		return 0;
	}
	const char *cmd = m_args.front();
	for (const Cmd *p = m_cmds; p->cmd; ++p)
	{
		if (strcmp(cmd, p->cmd) == 0)
		{
			return p->id;
		}
	}
//	clear();
	return -1;
}

int CmdLine::poll()
{
	const int c = getchar_timeout_us(0);
	if (c < 0)
		return -10;
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
		return evalLine();
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
	return -10;
}

