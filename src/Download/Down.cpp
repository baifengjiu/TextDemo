#include "Down.h"
#include <QNetworkRequest>
#include <QFileInfo>

Down::Down(QString file, QUrl url, QObject* parent)
	: QObject(parent)
	, m_url(url)
{
	m_downFile = new QFile(file);
	if (!m_downFile->open(QIODevice::WriteOnly))
	{
		return;
	}
	m_reply = m_networkManager.get(QNetworkRequest(url));
	connect(m_reply, SIGNAL(finished()), this, SLOT(onFinished()));
	connect(m_reply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
	connect(m_reply, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(progressValueChanged(qint64, qint64)));
}

Down::~Down()
{
}

void Down::setModelIndex(QModelIndex index)
{
	m_index = index;
}

void Down::onReadyRead()
{
	m_downFile->write(m_reply->readAll());
}

void Down::onFinished()
{
	QFileInfo fileInfo;
	fileInfo.setFile(m_downFile->fileName());
	m_downFile->close();
	delete m_downFile;
	m_downFile = nullptr;
	m_reply->deleteLater();
	m_reply = nullptr;
	emit finished();
}

void Down::onProgress(qint64 bytesRead, qint64 totalBytes)
{
	emit(m_index, bytesRead, totalBytes);
}
