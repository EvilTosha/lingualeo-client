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
		/* Parsing json data from reply */
		QByteArray data = reply->readAll();
		QJson::Parser parser;
		bool parseSuccess;
		QVariant parseResult = parser.parse(data, &parseSuccess);
		/* Error handling */
		if (!parseSuccess) {
			emit requestFailed(tr("Reply parse error"));
			return;
		}
		QString errorMsg = parseResult.toMap()["error_msg"].toString();
		if (errorMsg != "") {
			emit requestFailed(errorMsg);
			qDebug() << parseResult << endl;
			return;
		}
		/* Request type switch */
		QString path = reply->url().path();
		if (path.compare(LOGIN_PATH) == 0) {
			emit loginSucceed();
		}
		else if (path.compare(TRANSLATES_PATH) == 0) {
			emit wordTranslated(parseResult);
		}
		else if (path.compare(ADDWORD_PATH) == 0) {
			emit wordAdded();
		}
		else {

		}
	} else {
		int httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		emit requestFailed(tr("Error code: ") + QString::number(httpStatus));
		qDebug() << "Error : " << httpStatus << endl;
	}
	reply->deleteLater();
}

void Translater::postRequest(QNetworkRequest req, QByteArray postData) {
	/* Adding appropriate parameters and headers before sending request */
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	QVariant cookie;
	cookie.setValue(manager_->cookieJar()->cookiesForUrl(SITE_URL));
	req.setHeader(QNetworkRequest::CookieHeader, cookie);
	manager_->post(req, postData);
}

void Translater::login(QString email, QString password) {
	/* Login to lingualeo.ru */
	QUrl url(SITE_URL + LOGIN_PATH);
	url.addQueryItem("email", email);
	url.addQueryItem("password", password);
	url.addQueryItem("remember", "1");
	postRequest(QNetworkRequest(url));
}

void Translater::getTranslates(QString word, bool media) {
	/* Send request for translates for given word */
	QUrl url(SITE_URL + TRANSLATES_PATH);
	url.addQueryItem("word", word);
	if (media) {
		url.addQueryItem("include_media", "1");
	}
	QNetworkRequest req(url);
	postRequest(req);
}

void Translater::addWord(QString word, QString translate, QString context) {
	/* Send request for adding word in user's personal dictionary */
	QUrl url(SITE_URL + ADDWORD_PATH);
	url.addQueryItem("word", word);
	url.addQueryItem("tword", translate);
	url.addQueryItem("context", context);
	postRequest(QNetworkRequest(url));
}
