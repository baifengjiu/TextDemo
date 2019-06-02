#include "Download.h"
#include <QToolBar>
#include <DownInfo.h>
#include <qnetwork.h>

Download::Download(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.stopBtn->setCheckable(true);

	ui.splitter->setStretchFactor(0, 0);
	ui.splitter->setStretchFactor(1, 5);
	ui.splitter->setChildrenCollapsible(false);
	ui.splitter->setSizes({ 150,0 });
}

void Download::initAction()
{
	connect(ui.actionAdd_new_down, &QAction::triggered, this, &Download::addNewTask);
	connect(ui.addBtn, &QToolButton::clicked, this, &Download::addNewTask);
}

void Download::addNewTask()
{
	DownInfo dlg(this);
	if (dlg.exec() == QDialog::Accepted)
	{
		FileMsg* msg = dlg.msg();

	}
}
