// ******************************************************
// * copyright (C) 2022 by rbehm@ibb-aviotec.com
// * File: mainwindow.cpp
// * created 2022-12-14 with pro-config V0.2
// ******************************************************

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::quit()
{
	close();
}
