// ******************************************************
// * copyright (C) 2022 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 12/14/2022 by behm
// ******************************************************

#ifndef PICOFORM_H
#define PICOFORM_H

#include <QWidget>

namespace Ui {
class PicoForm;
}
class PicoPort;

class PicoForm : public QWidget
{
	Q_OBJECT

public:
	explicit PicoForm(QWidget *parent = nullptr);
	~PicoForm();
	PicoPort *port() const {  return m_port; }

protected:
	void changeEvent(QEvent *e);

private slots:
	void on_actionViewBin_triggered();
	void on_actionSelBin_triggered();
	void on_actionResetPico_triggered();
	void on_actionSelPicoDir_triggered();
	void devChanged(bool  on);
	void directoryChanged(const QString &path);
	void picoDirectoryChanged(const QString &path);

private:
	Ui::PicoForm *ui;
	PicoPort *m_port;
	QFileSystemWatcher *m_binDirWatcher;
	QFileSystemWatcher *m_picoDirWatcher;
	QMap<bool,QString> m_styles;
	void setBinDir(QString dn);
	void setPicoDir(QString dn);
	bool chkBin();
};

#endif // PICOFORM_H
