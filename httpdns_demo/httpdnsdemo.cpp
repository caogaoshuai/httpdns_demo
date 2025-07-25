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
    connect(ui.pushButton, &QPushButton::clicked, this, &HttpDnsDemo::clickbutton);
}

HttpDnsDemo::~HttpDnsDemo()
{}

void HttpDnsDemo::clickbutton()
{
    ui.textEdit->clear();
    QString strurl = ui.lineEdit->text().trimmed();
    if (strurl.isEmpty()) {
        ui.textEdit->append("地址为空");
        return;
    }

    QUrl url(strurl);

    // 创建线程与 Worker
    QThread* thread = new QThread;
    Worker* worker = new Worker(url);  // 构造函数传 QUrl

    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &Worker::process);

    connect(worker, &Worker::finished, this, [=](const QString& result) {
        ui.textEdit->append(result);

        thread->quit();
        thread->wait();
        worker->deleteLater();
        thread->deleteLater();
        });

    thread->start();
}


