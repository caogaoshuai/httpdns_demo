#include "httpdnsdemo.h"
#include <QPushButton>
#include <QLineEdit>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QtConcurrent/QtConcurrent>
#include <QNetworkReply>
#include <QTimer>
#include "HttpDns.h"

HttpDnsDemo::HttpDnsDemo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.centralWidget->layout();


	connect(ui.pushButton, &QPushButton::clicked, [this]() {
		ui.textEdit->clear();
		if (ui.lineEdit->text().isEmpty())
		{
			ui.textEdit->append("��ַΪ��");
			return;
		}
		auto strurl = ui.lineEdit->text();
		qDebug() << "ssl build:" << QSslSocket::sslLibraryBuildVersionString();


		qDebug() << "SSL library runtime version:" << QSslSocket::sslLibraryVersionString();


		qDebug() << "OpenSSL֧�����:" << QSslSocket::supportsSsl();

		QtConcurrent::run(worker, &Worker::doWork, strurl);
	});

	worker = new Worker();
	connect(worker, &Worker::resultReady, this, &HttpDnsDemo::clickButtonPostHandle);
	
  
}

HttpDnsDemo::~HttpDnsDemo()
{}


void HttpDnsDemo::clickButtonPostHandle(QNetworkRequest req)
{
	QByteArray content, verb;
	verb = "POST";

	QNetworkAccessManager access;
	access.clearAccessCache();

	QNetworkReply* reply = access.sendCustomRequest(req, verb, content);
	if (!reply)
	{
		ui.textEdit->append("�����쳣");
		return;
	}
	QEventLoop loop;
	loop.connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	QTimer::singleShot(5 * 1000, &loop, &QEventLoop::quit);
	loop.exec();
	if (!reply->isFinished())
	{
		ui.textEdit->append("Ӧ��ʱ");
		return;
	}
	QString error;
	error = reply->errorString();
	auto httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	auto data = reply->readAll();

	reply->deleteLater();
	if (httpStatusCode != 200)
	{
		ui.textEdit->append(QString::number(httpStatusCode));
		ui.textEdit->append(error);
		return;
	}
	else
	{
		ui.textEdit->append(data);
		return;
	}
}