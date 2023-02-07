// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/7/2023 by behm
// ******************************************************

#ifndef CMDLINE_H
#define CMDLINE_H

#include <vector>

struct Cmd
{
	int id;
	const char *cmd;
};

class CmdLine
{
public:
	enum R{ NoIn=-10, Unknown = -1, Empty=0 };
	CmdLine(const Cmd * const cmds, const char *dlm = " ,");
	int poll();
	void clear();
	const std::vector<const char *> &args() const { return m_args; }
	const char * argn(uint n) const;
	int num(uint n, uint base = 0) const;

protected:
	int evalLine();
	static constexpr int maxline = 80;
	int m_linelen;
	const char * const m_dlm;
	char m_line[maxline+1];
	const Cmd * const m_cmds;
	std::vector<const char*> m_args;
};

#endif // CMDLINE_H
