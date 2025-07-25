#include "httpdnsdemo.h"
#include <QPushButton>
#include <QLineEdit>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QThread>

#include "HttpDns.h"
#include "worker.h"


HttpDnsDemo::HttpDnsDemo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.centralWidget->layout();
    ui.lineEdit->setText("https://httpdns-sc.aliyuncs.com/139450/ss");
	manager = new QNetworkAccessManager(this);
    connect(ui.pushButton, &QPushButton::clicked, this, &HttpDnsDemo::clickbutton);
	connect(manager, &QNetworkAccessManager::finished, this, &HttpDnsDemo::onReplyFinished);
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
	

	manager->clearAccessCache();
	QNetworkReply* reply = manager->sendCustomRequest(req, verb, content);

}

/*

void HttpDnsDemo::onReplyFinished(QNetworkReply* reply)
{
    QThread::sleep(10);
    
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray data = reply->readAll();
    QString errorString = reply->errorString();

    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        ui.textEdit->append(QString("错误: %1").arg(errorString));
        ui.textEdit->append(QString("HTTP状态码: %1").arg(statusCode));
        return;
    }

    ui.textEdit->append(QString("响应状态码: %1").arg(statusCode));
    ui.textEdit->append("响应内容:");
    ui.textEdit->append(data);
}
*/

void HttpDnsDemo::onReplyFinished(QNetworkReply* reply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray data = reply->readAll();
    QString errorString = reply->errorString();

    reply->deleteLater();

    // 创建子线程 + worker
    QThread* thread = new QThread;
    Worker* worker = new Worker(data, statusCode);
    worker->moveToThread(thread);

    // 线程启动后执行 worker 的 process
    connect(thread, &QThread::started, worker, &Worker::process);

    // worker 发出 finished 信号后更新 UI
    connect(worker, &Worker::finished, this, [=](const QString& result) {
        ui.textEdit->append(result);

        // 清理线程和 worker
        thread->quit();
        thread->wait();
        worker->deleteLater();
        thread->deleteLater();
        });

    thread->start();
}


