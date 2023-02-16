// ******************************************************
// * copyright (C) 2023 by rbehm@ibb-aviotec.com
// * File: mainwindow.cpp
// * created 2023-02-14 with pro-config V0.2
// ******************************************************

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include "ipccomm.h"

bool  verbose = true;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	statusBar()->addPermanentWidget(m_portname = new QLabel);
	connect(ui->port, &SerialPortSelector::portChanged, this, &MainWindow::portChanged);
	QString port = Config::stringValue("port");
	ui->port->init(port);
	ui->txdata->setText(Config::stringValue("txdata"));
}

MainWindow::~MainWindow()
{
	Config::setValue("port", ui->port->portname());
	Config::setValue("txdata", ui->txdata->text());
	delete ui;
}

void MainWindow::quit()
{
	close();
}


void MainWindow::on_txdata_returnPressed()
{
	qDebug() << Q_FUNC_INFO;
	QByteArray d = ui->txdata->text().toLatin1();
	if (m_ipc)
	{
		m_ipc->txData(d);
	}
}

void MainWindow::portChanged(const QString portname)
{
	qDebug() << Q_FUNC_INFO << portname;
	if (m_ipc)
	{
		delete m_ipc;
	}
	m_ipc = new IpcComm(portname + ":115200", this);
	connect(m_ipc.data(), &IpcComm::error, this, &MainWindow::portError);
	connect(m_ipc.data(), &IpcComm::dataRxd, this, &MainWindow::dataRxd);
	m_portname->setText(m_ipc.data()->device());
}

void MainWindow::portError(QString msg)
{
	qDebug() << Q_FUNC_INFO << msg;
}

void MainWindow::dataRxd(const QByteArray d)
{
	qDebug() << Q_FUNC_INFO << d.toHex(' ');
}
