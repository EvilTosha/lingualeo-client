#include <QTextEdit>



#include "translater.h"


Translater::Translater(QObject *parent) :
  QObject(parent){
	_manager = new QNetworkAccessManager();
	connect(_manager, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)));

	QUrl url("http://lingualeo.ru/api/login");
	_loginUrl = url;
	QNetworkRequest req(_loginUrl);
	QByteArray postData;
	postData.append("remember=1&email=toshaevil%40gmail.com&password=1234567");
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	_manager->post(req, postData);

}

void Translater::loginCheck() {
	static bool a = false;
	if (a) {
		return;
	}
	a = true;
	QUrl url("http://lingualeo.ru/api/isauthorized");
	QNetworkRequest req(url);
	_manager->get(req);
}

void Translater::signIn(QString login, QString password) {

}

void Translater::replyFinished(QNetworkReply *reply) {
	if ((reply->error()) == QNetworkReply::NoError) {
		QByteArray array = reply->readAll();
		QTextEdit *e = new QTextEdit(byteArrayToString(array));
		e->show();
		QList<QNetworkCookie>  cookies = _manager->cookieJar()->cookiesForUrl(_loginUrl);
		qDebug() << "COOKIES for" << _loginUrl.host() << cookies;
		loginCheck();
	} else {
		//get http status code
		int httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		//do some error management
	}
	reply->deleteLater();
}


QString Translater::byteArrayToString(QByteArray ba) {
	QString res;
	for (char c : ba) {
		res += c;
	}
	return res;
}
