#include "DownInfo.h"
#include "ui_DownInfo.h"
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QProcess>

DownInfo::DownInfo(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::DownInfo)
	, m_fileMsg(new FileMsg)
{
	connect(ui->okButton, &QPushButton::clicked, this, &DownInfo::onEnsure);
	connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

DownInfo::~DownInfo()
{
	delete ui;
	delete m_fileMsg;
}

void DownInfo::setMsg(FileMsg* file)
{
	m_fileMsg = file;
	ui->okButton->setEnabled(false);
}

FileMsg* DownInfo::msg()
{
	return m_fileMsg;
}

void DownInfo::onProgressValue(qint64 bytesRead, qint64 totalBytes)
{
	qint64 value = bytesRead / totalBytes * 100;
	ui->progressBar->setValue(value);
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
	if (newUrl.isValid())
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

	QFile* file = new QFile(fullPath);
	if (!file->open(QIODevice::WriteOnly))
	{
		ui->tips->setText(tr("Open file error."));
		return;
	}

	m_fileMsg->url = newUrl;
	m_fileMsg->file = file;

	accept();
}
