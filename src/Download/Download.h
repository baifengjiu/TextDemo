#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Download.h"

class Download : public QMainWindow
{
	Q_OBJECT

public:
	Download(QWidget *parent = Q_NULLPTR);
	void initAction();

private Q_SLOTS:
	void addNewTask();
private:
	Ui::DownloadClass ui;
};
