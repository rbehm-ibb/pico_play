// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/7/2023 by behm
// ******************************************************

#ifndef CMDLINE_H
#define CMDLINE_H

#include <vector>
#include <iostream>


class CmdLine
{
public:
	class Args : public std::vector<const char*>
	{
		friend std::ostream &operator<<(std::ostream &s, const Args &d);
	public:
		Args() {}
		const char * argn(uint n) const;
		int num(int n, uint base = 0) const;
	};

	typedef void (*callback_t)(const Args &);
	struct Cmd
	{
		const char *cmd;
		callback_t callback;
	};
	enum R{ NoIn=-10, Unknown = -1, Empty=0 };
	CmdLine(const Cmd * const cmds, const char *dlm = " ,");
	int poll();
	void clear();
	const Args &args() const { return m_args; }
	const char * argn(uint n) const;
	int num(uint n, uint base = 0) const;

protected:
	void evalLine();
	static constexpr int maxline = 80;
	int m_linelen;
	char m_line[maxline+1];
	const Cmd * const m_cmds;
	const char * const m_dlm;
	Args m_args;
};

#endif // CMDLINE_H
