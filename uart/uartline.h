// ******************************************************
// * copyright (C) 2023 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/9/2023 by behm
// ******************************************************

#ifndef UARTLINE_H
#define UARTLINE_H

#include <string>
#include "uartbase.h"

///
/// \brief The Matcher class hsa a match string
/// and gets char after char and signals when the sequence matched the pattern
///
class Matcher
{
public:
	Matcher();
	void reset() { m_idx =  0; }
	bool tryMatch(char c);
	int idx() const { return m_idx; }
	void setMatch(const char *s);
	const  char *match() { return m_match; }
private:
	static constexpr int maxSeq = 10;	/// max allowed for leadin/leadout sequence;
	char m_match[maxSeq+1];
	int m_idx;
};

///
/// \brief The UartLine class is a Line oriented Uart
/// based on virtual base Uart which handles hardware setup and interrupt dispatch.
/// It accepts input lines starting with a leadin sequence and ending with an leaout sequence. Anything else gets ignored.
/// Sent lines are pre/appended with these sequences automatically.
///
class UartLine : public UartBase
{
public:
	UartLine(int uartIdx, int txPin =  -1, int rxPin = -1, int baud = 115200);
	virtual ~UartLine();
	bool hasRx() const { return m_hasLine; }
	bool getLine(char *s, size_t max);		/// s must be big enough
	std::string get();
	void put(const std::string &s);
	void putLine(const char *s);	/// send a line with leaadin/out pre/appended
	const char *leadin() { return m_inMatch.match(); }
	void setLeadin(const char *s) { m_inMatch.setMatch(s); }
	const char *leadout() { return m_outMatch.match(); }
	void setLeadout(const char *s) { m_outMatch.setMatch(s); }
	char ignore() const { return m_ignore; }
	void setIgnore(char ignore) { m_ignore = ignore; }

protected:
	void put(const char *s);
	void clearLine();
	static constexpr int maxLineLength = 100; /// anything longer will be cut off.
	bool m_hasLine;
	bool m_hadLeadin;
	int m_lineLen;
	char m_line[maxLineLength+1];	/// the rx buffer
	char m_ignore;		// these char will be ignored on rx (e.q. \r from \r\n)
	Matcher m_inMatch;
	Matcher m_outMatch;
	void uartIsr() override;	/// called on rx isr
	void charRxd(char c);
};

#endif // UARTLINE_H
