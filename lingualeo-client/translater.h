#ifndef TRANSLATER_H
#define TRANSLATER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QNetworkCookieJar>
#include <QDebug>

#include "QJson/parser.h"

class Translater : public QObject {
  Q_OBJECT
public:
  explicit Translater(QObject *parent = 0);

signals:
	void wordTranslated(QVariant translateData);
	void loginSucceed();
	void loginFailed(QString errorMsg = "");

public slots:
	void replyFinished(QNetworkReply *reply);
	void login(QString email, QString password);
	void getTranslates(QString word, bool media = true);
	void postRequest(QNetworkRequest req, QByteArray postData = "");

	// Setters

private:
	QNetworkAccessManager *manager_;
	static const QString SITE_URL;
	static const QString TRANSLATES_PATH;
	static const QString LOGIN_PATH;
	static const QString ADDWORD_PATH;
};

#endif // TRANSLATER_H
