#pragma once

#include <QDialog>
#include <QUrl>
#include <QFile>

namespace Ui { class DownInfo; }

struct FileMsg
{
	FileMsg() {};
	~FileMsg() { delete file; };

	QUrl url;
	QFile * file;
};

class DownInfo : public QDialog
{
	Q_OBJECT

public:
	DownInfo(QWidget* parent = nullptr);
	~DownInfo();

	void setMsg(FileMsg *file);

	FileMsg* msg();

public Q_SLOTS:
	void onProgressValue(qint64,qint64);

private Q_SLOTS:
	void onEnsure();
private:
	Ui::DownInfo* ui;
	FileMsg* m_fileMsg;
}