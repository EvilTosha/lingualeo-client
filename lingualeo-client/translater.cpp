#include <QTextEdit>

#include "translater.h"

const QUrl Translater::SITE_URL("http://lingualeo.ru/");


Translater::Translater(QObject *parent) :
  QObject(parent){
	manager_ = new QNetworkAccessManager();
	connect(manager_, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)));

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
		QList<QNetworkCookie>  cookies = manager_->cookieJar()->cookiesForUrl(SITE_URL);
		qDebug() << "COOKIES for" << SITE_URL.host() << cookies;

		/* Debug only staff */
		static bool a = 0;
		if (a) { return; }
		a = 1;
		getTranslates("opacity");
		/* End of debug staff */

	} else {
		//get http status code
		int httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		qDebug() << "Error : " << httpStatus << endl;
		//exit(0);
		//do some error management
	}
	reply->deleteLater();
}

void Translater::signIn(QString login, QString password) {
	QUrl url(SITE_URL.toString() + "api/login");
	url.addQueryItem("email", login);
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
	QUrl url(SITE_URL.toString() + "api/gettranslates");
	url.addQueryItem("word", word);
	if (media) {
		url.addQueryItem("include_media", "1");
	}
	QNetworkRequest req(url);
	postRequest(req);
}
