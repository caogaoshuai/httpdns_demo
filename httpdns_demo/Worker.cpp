#include "Worker.h"



void Worker::doWork(const QString strurl) {
	qDebug() << "Running in background thread:" << QThread::currentThread();
	QUrl url(strurl);

	QNetworkRequest req(url);

	QByteArray content, verb;
	verb = "POST";
	req.setPeerVerifyName(url.host());
	req.setRawHeader("Host", url.host().toUtf8());
	req.setUrl(Resolve(url));
	qDebug() << "url:" << req.url().toString();
	emit resultReady(req);
}