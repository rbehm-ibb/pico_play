// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/14/2022 by behm
// ******************************************************

#include "picoform.h"
#include "ui_picoform.h"
#include "config.h"
#include "picoport.h"

PicoForm::PicoForm(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::PicoForm)
	, m_port(new PicoPort(this))
	, m_binDirWatcher(new QFileSystemWatcher(this))
	, m_picoDirWatcher(new QFileSystemWatcher(this))
{
	ui->setupUi(this);
	m_styles.insert(false, "* { background: #ffff60; }");
	m_styles.insert(true, "* { background: #60ff60; }");
	ui->binDir->addAction(ui->actionSelBin, QLineEdit::TrailingPosition);
	ui->binDir->addAction(ui->actionViewBin, QLineEdit::TrailingPosition);
	ui->picoPort->addAction(ui->actionResetPico, QLineEdit::TrailingPosition);
//	ui->picoPort->addAction(ui->actionMinicom, QLineEdit::TrailingPosition);
	ui->picoDir->addAction(ui->actionSelPicoDir, QLineEdit::TrailingPosition);
	connect(m_port, &PicoPort::devChanged, this, &PicoForm::devChanged);
	connect(m_binDirWatcher, &QFileSystemWatcher::directoryChanged, this, &PicoForm::binDirectoryChanged);
	connect(m_picoDirWatcher, &QFileSystemWatcher::directoryChanged, this, &PicoForm::picoDirectoryChanged);
	devChanged(m_port->isOpen());
	setBinDir(Config::stringValue("picoForm/bindir"));
	setPicoDir(Config::stringValue("picoForm/picoDir"));
}

PicoForm::~PicoForm()
{
	Config::setValue("picoForm/bindir", ui->binDir->text());
	Config::setValue("picoForm/picoDir", ui->picoDir->text());
	delete ui;
}

void PicoForm::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void PicoForm::on_actionViewBin_triggered()
{
	QDesktopServices::openUrl(ui->binDir->text());
}

void PicoForm::on_actionSelBin_triggered()
{
	QString dn = QFileDialog::getExistingDirectory(this, "Bin directory", ui->binDir->text());
	if (!dn.isNull())
	{
		setBinDir(dn);
	}
}

void PicoForm::on_actionResetPico_triggered()
{
	m_port->boot();
}

void PicoForm::on_actionSelPicoDir_triggered()
{
	QString dir = QFileDialog::getExistingDirectory(this, "Pico Dir", ui->picoDir->text());
	if (! dir.isNull())
	{
		setPicoDir(dir);
	}
}

void PicoForm::devChanged(bool on)
{
	ui->picolab->setStyleSheet(m_styles.value(on));
	ui->picoPort->setText(m_port->device());
	ui->actionResetPico->setEnabled(on);
}

void PicoForm::binDirectoryChanged(const QString &path)
{
	qDebug() << Q_FUNC_INFO << path;
	chkBin();
}

void PicoForm::picoDirectoryChanged(const QString &path)
{
	qDebug() << Q_FUNC_INFO << path;
	setPicoDir(ui->picoDir->text());
	QDir dir(ui->picoDir->text());
	ui->picodirlab->setStyleSheet(m_styles.value(dir.exists()));
}

void PicoForm::setBinDir(QString dn)
{
	ui->binDir->setText(dn);
//	qDebug() << Q_FUNC_INFO << m_watcher->files() << m_watcher->directories();
	if (!m_binDirWatcher->directories().isEmpty())
	{
		m_binDirWatcher->removePaths(m_binDirWatcher->directories());
	}
	m_binDirWatcher->addPath(dn);
//	qDebug() << Q_FUNC_INFO << m_watcher->files() << m_watcher->directories();
	chkBin();
}

void PicoForm::setPicoDir(QString dn)
{
	ui->picoDir->setText(dn);
	int i = dn.lastIndexOf('/');
	if (i >= 0)
	{
		dn = dn.left(i);
	}
	QDir dir(dn);
	// cdUp() does not work is dir not exists !
	while (! dir.exists())
	{
		int i = dn.lastIndexOf('/');
		if (i >= 0)
		{
			dn = dn.left(i);
		}
		dir.setPath(dn);
	}
	const QStringList sdir = m_picoDirWatcher->directories();
	if (! sdir.isEmpty())
	{
		m_picoDirWatcher->removePaths(sdir);
	}
	m_picoDirWatcher->addPath(dir.absolutePath());
//	qDebug() << Q_FUNC_INFO << dir << dn << m_picoDirWatcher->directories();
}

bool PicoForm::chkBin()
{
	const QStringList sdir = m_binDirWatcher->directories();
//	qDebug()  <<  Q_FUNC_INFO << sdir;
	if (! sdir.isEmpty())
	{
		QDir dir (sdir.first(), "*.uf2", QDir::NoSort, QDir::Files);
		const QStringList fns = dir.entryList();
//		qDebug() << Q_FUNC_INFO << dir << fns;
		if (! fns.isEmpty())
		{
			ui->binFile->setText(fns.first());
			ui->binflab->setStyleSheet(m_styles.value(true));
			return true;
		}
		else
		{
			ui->binFile->setText(QString());
			ui->binflab->setStyleSheet(m_styles.value(false));
			return false;
		}
	}
	return false;
}


