// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/7/2023 by behm
// ******************************************************

#ifndef CMDLINE_H
#define CMDLINE_H

#include <vector>
#include <iostream>

///
/// \brief The CmdLine class is a handler for  command input (via stdin,USB,Serial)
///
/// It is given a list of commands (struct Cmd ) after input of a line (\n  or \r)
/// this line is split in Args at the define delim and the  the command list is search for the first word.
/// If found the corresponding callback is called with the list of args.
/// To keep CmdLine alive call  it periodically via poll.
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
		std::vector<uint8_t> asVecu8(int n) const;
	};

	typedef void (*callback_t)(const Args &);
	struct Cmd
	{
		const char *cmd;
		callback_t callback;
	};

	CmdLine(const Cmd * const cmds, const char *dlm = " ,");
	void poll();
	void clear();

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
