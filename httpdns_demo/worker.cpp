// worker.cpp

#include "worker.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QSslSocket>
#include <QThread>
#include "HttpDns.h"

Worker::Worker(const QUrl& url, QObject* parent)
    : QObject(parent), url_(url)
{}

void Worker::process()
{
    QString result;

    /*
    result += "ssl build: " + QSslSocket::sslLibraryBuildVersionString() + "\n";
    result += "SSL library runtime version: " + QSslSocket::sslLibraryVersionString() + "\n";
    result += "OpenSSL支持情况: " + QString::number(QSslSocket::supportsSsl()) + "\n";
    */

    QNetworkRequest req;
    req.setPeerVerifyName(url_.host());
    req.setRawHeader("Host", url_.host().toUtf8());
    QThread::sleep(10);         // 模拟HTTPDNS访问超时
    req.setUrl(Resolve(url_));  // 使用自定义 HTTPDNS 解析函数

    QNetworkAccessManager manager;
    QEventLoop loop;
    QByteArray content;  // 空内容
    QNetworkReply* reply = manager.sendCustomRequest(req, "POST", content);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray data = reply->readAll();
    QString errorString = reply->errorString();

    if (reply->error() != QNetworkReply::NoError) {
        result += QString("error: %1\nstatus code: %2\n").arg(errorString).arg(statusCode);
    }
    else {
        result += QString("status code: %1\n response body:\n%2").arg(statusCode).arg(QString::fromUtf8(data));
    }

    reply->deleteLater();

    emit finished(result);
}
