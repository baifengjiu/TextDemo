#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>

class Down : public QObject
{
	Q_OBJECT

public:
	Down(QFile file, QUrl url,QObject *parent);
	~Down();

public Q_SLOTS:
	void onReadyRead();
	void onFinished();

Q_SIGNALS:
	void progressValueChanged(qint64, qint64);

private:
	QNetworkAccessManager m_networkManager;
	QNetworkReply* m_reply; //������Ӧ
	QFile m_downFile;//���ر������ʱ�ļ�
	QUrl m_url;
};
