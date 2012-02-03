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
	void wordAdded();
	void loginSucceed();
	void requestFailed(QString errorMsg = "");

public slots:
	/* LinguaLeo.ru API functions */
	void login(QString &email, QString &password) const;
	void getTranslates(QString &word, bool media = true);
	void addWord(QString &word, QString &translate, QString context = "");

	/* Serve functions */
	void postRequest(QUrl &url, QByteArray postData = "") const;
	void getRequest(QUrl &url) const;
	void replyFinished(QNetworkReply *reply);

	// Setters

private:
	QNetworkRequest wrappedRequest(QUrl &url) const;

	QNetworkAccessManager *manager_;
	static const QString SITE_URL;
	static const QString TRANSLATES_PATH;
	static const QString LOGIN_PATH;
	static const QString ADDWORD_PATH;
};

#endif // TRANSLATER_H
