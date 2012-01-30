#include "translater.h"

const QString Translater::SITE_URL("http://lingualeo.ru");
const QString Translater::TRANSLATES_PATH("/api/gettranslates");
const QString Translater::LOGIN_PATH("/api/login");
const QString Translater::ADDWORD_PATH("/api/addword");


Translater::Translater(QObject *parent) :
  QObject(parent){
	manager_ = new QNetworkAccessManager();
	connect(manager_, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)));
}


void Translater::replyFinished(QNetworkReply *reply) {
	if ((reply->error()) == QNetworkReply::NoError) {
		QString path = reply->url().path();
		QByteArray data = reply->readAll();
		QJson::Parser parser;
		bool parseSuccess;
		QVariant parseResult = parser.parse(data, &parseSuccess);
		if (path.compare(LOGIN_PATH) == 0) {
			if (!parseSuccess) {
				emit loginFailed(tr("Reply parse error"));
				return;
			}
			QString errorMsg = parseResult.toMap()["error_msg"].toString();
			if (errorMsg != "") {
				emit loginFailed(errorMsg);
				return;
			}
			emit loginSucceed();
		}
		else if (path.compare(TRANSLATES_PATH) == 0) {

		}
		else if (path.compare(ADDWORD_PATH) == 0) {

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
