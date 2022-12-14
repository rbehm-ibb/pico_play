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
	startTimer(100);
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
	static bool inside = false;
	if (inside)
	{
		qDebug() << Q_FUNC_INFO << inside;
		return;
	}
	inside = true;
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
		QElapsedTimer timer;
		timer.start();
		while (timer.elapsed() < 1000)
		{
		}
		setPort(m_devInfo);
		setBaudRate(m_baud);
		while (! open(QIODevice::ReadWrite))
		{
			qWarning() << Q_FUNC_INFO << timer.elapsed() * 1e-3 << portName() << errorString();
			if (timer.elapsed() > 10 * 1000)
				break;;
		}
		setBaudRate(m_baud);
		setParity(QSerialPort::NoParity);
		setDataBits(QSerialPort::Data8);
		setFlowControl(QSerialPort::NoFlowControl);
		emit devChanged(isOpen());
	}
	inside = false;
}
