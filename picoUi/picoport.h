// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/14/2022 by behm
// ******************************************************

#ifndef PICOPORT_H
#define PICOPORT_H

#include "ibserialportline.h"

class PicoPort : public IBSerialPort
{
	Q_OBJECT
public:
	PicoPort(QObject *parent);
	~PicoPort();
	void boot();
signals:
	void  devChanged(bool  on);
private slots:
	void lostPortErrorSl();


	// QObject interface
protected:
	void timerEvent(QTimerEvent *event) override;
	uint m_baud;
};

#endif // PICOPORT_H
