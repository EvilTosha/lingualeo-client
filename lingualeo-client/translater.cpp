#include "translater.h"

const QString Translater::SITE_URL("http://lingualeo.ru/");
const QString Translater::TRANSLATES_PATH("api/gettranslates");
const QString Translater::LOGIN_PATH("api/login");
const QString Translater::ADDWORD_PATH("api/addword");


Translater::Translater(QObject *parent) :
  QObject(parent){
	manager_ = new QNetworkAccessManager();
	connect(manager_, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)));
}


void Translater::replyFinished(QNetworkReply *reply) {
	if ((reply->error()) == QNetworkReply::NoError) {
		QByteArray data = reply->readAll();
		QString path = reply->url().path();
		if (path == LOGIN_PATH) {

		}
		else if (path == TRANSLATES_PATH) {

		}
		else if (path == ADDWORD_PATH) {

		}
		else {

		}
	} else {
		//get http status code
		int httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		qDebug() << "Error : " << httpStatus << endl;
		//exit(0);
		//do some error management
	}
	reply->deleteLater();
}

void Translater::login(QString email, QString password) {
	QUrl url(SITE_URL + LOGIN_PATH);
	url.addQueryItem("email", email);
	url.addQueryItem("password", password);
	url.addQueryItem("remember", "1");
	postRequest(QNetworkRequest(url));
}

void Translater::postRequest(QNetworkRequest req, QByteArray postData) {
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	QVariant cookie;
	cookie.setValue(manager_->cookieJar()->cookiesForUrl(SITE_URL));
	req.setHeader(QNetworkRequest::CookieHeader, cookie);
	manager_->post(req, postData);
}

void Translater::getTranslates(QString word, bool media) {
	QUrl url(SITE_URL + TRANSLATES_PATH);
	url.addQueryItem("word", word);
	if (media) {
		url.addQueryItem("include_media", "1");
	}
	QNetworkRequest req(url);
	postRequest(req);
}
