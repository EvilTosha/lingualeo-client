#include <QDateTime>
#include <QPixmap>

#include "translater.h"

const QString Translater::SITE_URL("http://lingualeo.ru");
const QString Translater::TRANSLATES_PATH("/api/gettranslates");
const QString Translater::LOGIN_PATH("/api/login");
const QString Translater::ADDWORD_PATH("/api/addword");
const QString Translater::PICTURE_PREFIX("/uploads/picture/");


Translater::Translater(QObject *parent) :
  QObject(parent){
	manager_ = new QNetworkAccessManager();
	connect(manager_, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)));
}


void Translater::replyFinished(QNetworkReply *reply) {
	if ((reply->error()) == QNetworkReply::NoError) {
		QString path = reply->url().path();
		if (path.contains(PICTURE_PREFIX)) {
			/* Picture processing */
			QPixmap *pixmap = new QPixmap();
			pixmap->loadFromData(reply->readAll());
			QString word = reply->url().queryItemValue("word");
			emit pictureGot(word, pixmap);
		}
		else {
			/* Parsing json data from reply */
			QByteArray data = reply->readAll();
			QJson::Parser parser;
			bool parseSuccess;
			QVariant parseResult = parser.parse(data, &parseSuccess);
			/* Error handling */
			if (!parseSuccess) {
				emit requestFailed(tr("Error: Reply parse error"));
				return;
			}
			QString errorMsg = parseResult.toMap()["error_msg"].toString();
			if (errorMsg != "") {
				emit requestFailed(errorMsg);
				return;
			}

			/* Request type switch */
			if (path.compare(LOGIN_PATH) == 0) {
				emit loginSucceed();
			}
			else if (path.compare(TRANSLATES_PATH) == 0) {
				QString hash = reply->url().queryItemValue("hash");
				emit wordTranslated(hashes_[hash], parseResult);
			}
			else if (path.compare(ADDWORD_PATH) == 0) {
				QString translate = parseResult.toMap()["translate_value"].toString();
				emit wordAdded(translate);
			}
			else {

			}
		}
	} else {
		int httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		emit requestFailed(tr("Error: code: ") + QString::number(httpStatus));
	}
	reply->deleteLater();
}

QNetworkRequest Translater::wrappedRequest(QUrl &url) const {
	/* Adding appropriate parameters and headers before sending request */
	QNetworkRequest req(url);
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	return req;
}

void Translater::postRequest(QUrl &url, QByteArray postData) const {
	manager_->post(wrappedRequest(url), postData);
}

void Translater::getRequest(QUrl &url) const {
	manager_->get(wrappedRequest(url));
}

QString Translater::getHash(const QString word) const {
	return QString::number(QDateTime::currentMSecsSinceEpoch()) + word;
}

QString Translater::addHashWord(const QString word) {
	QString hash = getHash(word);
	if (!hashes_.contains(hash)) {
		hashes_[hash] = word;
	}
	return hash;
}

void Translater::login(QString email, QString password) const {
	/* Login to lingualeo.ru */
	QUrl url(SITE_URL + LOGIN_PATH);
	url.addQueryItem("email", email);
	url.addQueryItem("password", password);
	url.addQueryItem("remember", "1");
	getRequest(url);
}

void Translater::getTranslates(QString word, bool media) {
	/* Send request for translates for given word */
	QUrl url(SITE_URL + TRANSLATES_PATH);
	url.addQueryItem("word", word);
	url.addQueryItem("hash", addHashWord(word));
	if (media) {
		url.addQueryItem("include_media", "1");
	}
	getRequest(url);
}

void Translater::getPicture(QString word, QString path) {
	/* Send request for picture for given word */
	QUrl url(path);
	url.addQueryItem("word", word);
	getRequest(url);
}

void Translater::addWord(QString word, QString translate, QString context) {
	/* Send request for adding word in user's personal dictionary */
	QUrl url(SITE_URL + ADDWORD_PATH);
	url.addQueryItem("word", word);
	url.addQueryItem("tword", translate);
	url.addQueryItem("context", context);
	getRequest(url);
}
