#include "httpdnsdemo.h"
#include <QPushButton>
#include <QLineEdit>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include "HttpDns.h"

HttpDnsDemo::HttpDnsDemo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.centralWidget->layout();

    connect(ui.pushButton, &QPushButton::clicked, this, &HttpDnsDemo::clickbutton);
}

HttpDnsDemo::~HttpDnsDemo()
{}

void HttpDnsDemo::clickbutton()
{
    ui.textEdit->clear();
    if (ui.lineEdit->text().isEmpty())
    {
        ui.textEdit->append("地址为空");
        return;
    }
	auto strurl = ui.lineEdit->text();
	qDebug() << "ssl build:" << QSslSocket::sslLibraryBuildVersionString();


	qDebug() << "SSL library runtime version:" << QSslSocket::sslLibraryVersionString();


	qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();

	QUrl url(strurl);
	
	QNetworkRequest req(url);

	QByteArray content, verb;
	verb = "POST";
	req.setPeerVerifyName(url.host());
	req.setRawHeader("Host", url.host().toUtf8());
	req.setUrl(Resolve(url));
	qDebug() << "url:" << req.url().toString();
	




	QNetworkAccessManager access;
	access.clearAccessCache();

	QNetworkReply* reply = access.sendCustomRequest(req, verb, content);
	if (!reply)
	{
		ui.textEdit->append("网络异常");
		return;
	}
	QEventLoop loop;
	loop.connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	QTimer::singleShot(5 * 1000, &loop, &QEventLoop::quit);
	loop.exec();
	if (!reply->isFinished())
	{
		ui.textEdit->append("应答超时");
		return ;
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