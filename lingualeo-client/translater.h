#ifndef TRANSLATER_H
#define TRANSLATER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QNetworkCookieJar>
#include <QDebug>

class Translater : public QObject {
  Q_OBJECT
public:
  explicit Translater(QObject *parent = 0);

	QString byteArrayToString(QByteArray ba);
  
signals:
  
public slots:
	void replyFinished(QNetworkReply *reply);
	void signIn(QString login, QString password);
	//	Development only staff
	void  loginCheck();

private:
	QNetworkAccessManager *_manager;
	QUrl _loginUrl;

};

#endif // TRANSLATER_H
