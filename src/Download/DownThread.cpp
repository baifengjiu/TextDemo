#include "DownThread.h"
#include <QNetworkRequest>
#include <QFileInfo>

Down::Down(QFile file, QUrl url, QObject* parent)
	: QObject(parent)
	, m_downFile(file)
	, m_url(url)
{
	m_reply = m_networkManager.get(QNetworkRequst(url));
	connect(m_reply, SIGNAL(finished()), this, SLOT(onFinished()));
	connect(m_reply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
	connect(m_reply, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(progressValueChanged(qint64, qint64)));
}

Down::~Down()
{
}

void Down::onReadyRead()
{
	m_downFile->write(m_reply->readAll());
}

void Down::onFinished()
{
	QFileInfo fileInfo;
	fileInfo.setFile(m_downFile.fileName());
	m_downFile.close();
	m_reply->deleteLater();
	m_reply = nullptr;
}
