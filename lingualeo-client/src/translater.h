#ifndef TRANSLATER_H
#define TRANSLATER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkCookieJar>
#include <QDebug>

#include "parser.h"

class Translater : public QObject {
  Q_OBJECT
public:
  explicit Translater(QObject *parent = 0);

signals:
	void wordTranslated(QString word, QVariant translateData);
	void wordAdded(QString translate);
	void loginSucceed();
	void requestFailed(QString errorMsg = "");
	void pictureGot(QString word, QPixmap *picture);

public slots:
	/* LinguaLeo.ru API functions */
	void login(QString email, QString password) const;
	void getTranslates(QString word, bool media = true);
	void getPicture(QString word, QString path);
	void addWord(QString word, QString translate, QString context = "");

private slots:
	/* Serve functions */
	void postRequest(QUrl &url, QByteArray postData = "") const;
	void getRequest(QUrl &url) const;
	void replyFinished(QNetworkReply *reply);
	QString addHashWord(const QString word);

private:
	QNetworkRequest wrappedRequest(QUrl &url) const;
	QString getHash(const QString word) const;
	QMap<QString, QString>  hashes_;

	QNetworkAccessManager *manager_;
	static const QString SITE_URL;
	static const QString TRANSLATES_PATH;
	static const QString LOGIN_PATH;
	static const QString ADDWORD_PATH;
	static const QString PICTURE_PREFIX;
};

#endif // TRANSLATER_H
