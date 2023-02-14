// ******************************************************
// * copyright (C) 2023 by rbehm@ibb-aviotec.com
// * File: mainwindow.h
// * created 2023-02-14 with pro-config V0.2
// ******************************************************

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class IpcComm;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

public slots:
	void quit();
private slots:
	void on_txdata_returnPressed();
	void portChanged(const QString portname);
	void portError(QString msg);
	void dataRxd(const QByteArray d);

private:
	Ui::MainWindow *ui;
	QPointer<IpcComm> m_ipc;
	QLabel *m_portname;
};

#endif // MAINWINDOW_H

