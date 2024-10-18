#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_httpdnsdemo.h"
#include <QPushButton>
#include <QLineEdit>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QtConcurrent/QtConcurrent>
#include <QNetworkReply>
#include <QTimer>
#include "Worker.h"

class HttpDnsDemo : public QMainWindow
{
    Q_OBJECT

public:
    HttpDnsDemo(QWidget *parent = nullptr);
    ~HttpDnsDemo();

public slots:
	void clickButtonPostHandle(QNetworkRequest req);
private:
    Ui::httpdnsdemo ui;
    Worker* worker;
};
