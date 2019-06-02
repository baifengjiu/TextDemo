#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>
#include <QModelIndex>

class Down : public QObject
{
	Q_OBJECT

public:
	Down(QString file, QUrl url, QObject *parent);
	~Down();
	void setModelIndex(QModelIndex index);

public Q_SLOTS:
	void onReadyRead();
	void onFinished();
	void onProgress(qint64, qint64);

Q_SIGNALS:
	void finished();
	void info(QModelIndex index,qint64, qint64);

private:
	QNetworkAccessManager m_networkManager;
	QNetworkReply* m_reply; //网络响应
	QFile *m_downFile;//下载保存的临时文件
	QUrl m_url;
	QModelIndex m_index;
};
