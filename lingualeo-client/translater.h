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
  
signals:
	void wordTranslated(QVariant translateData);

	QNetworkReply* curReply() const;
	QString curWord() const;

public slots:
	void replyFinished(QNetworkReply *reply);
	void signIn(QString login, QString password);
	void getTranslates(QString word, bool media = true);
	void postRequest(QNetworkRequest req, QByteArray postData = "");

	// Setters

private:
	QNetworkAccessManager *manager_;
	static const QUrl SITE_URL;
};

#endif // TRANSLATER_H
