#include "Download.h"
#include <QToolBar>
#include <qabstractitemmodel.h>
#include "DownInfo.h"
#include "Down.h"

Download::Download(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.stopBtn->setCheckable(true);

	ui.splitter->setStretchFactor(0, 0);
	ui.splitter->setStretchFactor(1, 5);
	ui.splitter->setChildrenCollapsible(false);
	ui.splitter->setSizes({ 150,0 });

	m_model = new MyTabelModel(ui.treeView);
	ui.tableView->setModel(m_model);

	initAction();
}

void Download::initAction()
{
	connect(ui.actionAdd_new_down, &QAction::triggered, this, &Download::addNewTask);
	connect(ui.addBtn, &QToolButton::clicked, this, &Download::addNewTask);
}

void Download::onInfo(QModelIndex index,qint64 bytesRead, qint64 totalBytes)
{	
	QModelIndex newIndex = m_model->index(index.row(),2);
	m_model->setData(newIndex,bytesRead);
	newIndex = m_model->index(index.row(), 1);
	m_model->setData(newIndex, totalBytes);
}

void Download::addNewTask()
{
	DownInfo dlg(this);
	if (dlg.exec() == QDialog::Accepted)
	{
		FileMsg msg = dlg.msg();
		QStringList data;
		data << msg.file << "" << "0%" << "" << "";
		m_model->addRowData(data);
		Down* down = new Down(msg.file,msg.url,this);
		QModelIndex index = m_model->index(m_model->rowCount(), 0);
		down->setModelIndex(index);
		connect(down,&Down::finished, down, &QObject::deleteLater);
		connect(down, &Down::info, this,&Download::onInfo);
	}
}
