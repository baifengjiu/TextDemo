#pragma once

#include <QDialog>
#include <QUrl>
#include <QFile>

namespace Ui { class DownInfo; };

struct FileMsg
{
	QUrl url;
	QString file;
};

class DownInfo : public QDialog
{
	Q_OBJECT

public:
	DownInfo(QWidget* parent = nullptr);
	~DownInfo();

	void setMsg(FileMsg file);

	FileMsg msg();


private Q_SLOTS:
	void onEnsure();

private:
	Ui::DownInfo* ui;
	FileMsg m_fileMsg;
};