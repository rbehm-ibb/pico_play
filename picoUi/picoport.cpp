// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/14/2022 by behm
// ******************************************************

#include "picoport.h"

PicoPort::PicoPort(QObject *parent)
	: IBSerialPort(0x2e8a, 0x000a, QString(), 115200, parent)
{
	if (isOpen())
	{
		m_baud = QSerialPort::baudRate();
	}
//	qDebug() << Q_FUNC_INFO << device() << m_baud;
	startTimer(1000);
}

PicoPort::~PicoPort()
{
	qDebug() << Q_FUNC_INFO;
}

void PicoPort::boot()
{
	if (isOpen())
	{
		QSerialPort::setBaudRate(1200);
	}
}

void PicoPort::lostPortErrorSl()
{
	qDebug() << Q_FUNC_INFO;
}


void PicoPort::timerEvent(QTimerEvent *event)
{
	Q_UNUSED(event)
	bool exist = QFile::exists(m_devInfo.systemLocation());
	if (isOpen())
	{
//		qDebug() << Q_FUNC_INFO << "o" << exist << m_devInfo.systemLocation();
		if (! exist)
		{
			close();
			emit devChanged(false);
		}
	}
	else if (exist)
	{
//		qDebug() << Q_FUNC_INFO << "c" << exist;
		setPort(m_devInfo);
		if (! open(QIODevice::ReadWrite))
		{
			qWarning() << Q_FUNC_INFO << portName() << errorString();
			return;
		}
		setBaudRate(m_baud);
		setParity(QSerialPort::NoParity);
		setDataBits(QSerialPort::Data8);
		setFlowControl(QSerialPort::NoFlowControl);
		emit devChanged(true);
	}
}
