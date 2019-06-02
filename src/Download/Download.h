#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Download.h"
#include "MyTabelModel.h"

class Download : public QMainWindow
{
	Q_OBJECT

public:
	Download(QWidget *parent = Q_NULLPTR);
	void initAction();

private Q_SLOTS:
	void addNewTask();
	void onInfo(QModelIndex index,qint64 bytesRead, qint64 totalBytes);
	
private:
	Ui::DownloadClass ui;
	MyTabelModel *m_model;
};
