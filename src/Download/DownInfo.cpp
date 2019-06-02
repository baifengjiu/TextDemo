#include "DownInfo.h"
#include "ui_DownInfo.h"
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QProcess>

DownInfo::DownInfo(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::DownInfo)
{
	ui->setupUi(this);

	connect(ui->okButton, &QPushButton::clicked, this, &DownInfo::onEnsure);
	connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

DownInfo::~DownInfo()
{
	delete ui;
}

void DownInfo::setMsg(FileMsg file)
{
	m_fileMsg = file;
	ui->okButton->setEnabled(false);
}

FileMsg DownInfo::msg()
{
	return m_fileMsg;
}

void DownInfo::onEnsure()
{
	QString urlSpec = ui->urlLe->text().trimmed();
	if (urlSpec.isEmpty())
	{		
		ui->urlLe->setFocus();
		ui->tips->setText(tr("Make the URL you need to download."));
		return;
	}

	QUrl newUrl = QUrl::fromUserInput(urlSpec);
	if (!newUrl.isValid())
	{
		ui->urlLe->setFocus();
		ui->tips->setText(tr("Invalid URL."));
		return;
	}

	QString tempDir = ui->tempPathLe->text().trimmed();
	if (tempDir.isEmpty())
	{
		ui->tempPathLe->setFocus();
		ui->tips->setText(tr("Please specify a directory to save the downloaded files."));
		return;
	}

	QString fullPath = tempDir + newUrl.fileName();
	if (QFile::exists(fullPath))
	{
		QFile::remove(fullPath);
	}

	m_fileMsg.url = newUrl;
	m_fileMsg.file = fullPath;
	accept();
}
