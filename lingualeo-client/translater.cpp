#include <QTextEdit>

#include "translater.h"


Translater::Translater(QObject *parent) :
  QObject(parent){
	_manager = new QNetworkAccessManager();
	connect(_manager, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)));
	_loginUrl = QUrl("http://lingualeo.ru/api/login");
	_curReply = nullptr;

	signIn("toshaevil@gmail.com", "1234567");
}


void Translater::replyFinished(QNetworkReply *reply) {
	if ((reply->error()) == QNetworkReply::NoError) {
		qDebug() << reply->request().url() << endl;
		for (auto header : reply->request().rawHeaderList()) {
			qDebug() << QString::fromUtf8(header) << " " <<
									QString::fromUtf8(reply->request().rawHeader(header)) << endl;
		}
		qDebug() << QString::fromUtf8(reply->request().attribute(QNetworkRequest::CustomVerbAttribute).toByteArray()) << endl;
		QByteArray array = reply->readAll();
		QTextEdit *e = new QTextEdit(QString::fromUtf8(array));
		e->show();
		QList<QNetworkCookie>  cookies = _manager->cookieJar()->cookiesForUrl(_loginUrl);
		qDebug() << "COOKIES for" << _loginUrl.host() << cookies;
	} else {
		//get http status code
		int httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		qDebug() << "Error : " << httpStatus << endl;
		//do some error management
	}
	reply->deleteLater();
}

void Translater::signIn(QString login, QString password) {
	QNetworkRequest req(_loginUrl);
	QByteArray postData;
	postData.append("remember=1&email=" + QUrl::toPercentEncoding(login) +
									"&password=" + QUrl::toPercentEncoding(password));
	postRequest(req, postData);
}

void Translater::postRequest(QNetworkRequest req, QByteArray postData) {
	if (_curReply) {
		_curReply->abort();
	}
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	_curReply = _manager->post(req, postData);
}

void Translater::getTranslates(QString word, bool media) {
	_curWord = word;
	QNetworkRequest req(QUrl("http://lingualeo.ru/api/gettranslates"));
	QByteArray postData;
	postData.append("word=" + word + (media ? "include_media=1" : ""));
	postRequest(req, postData);
}
