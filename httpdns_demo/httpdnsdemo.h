#pragma once

#include <QtWidgets/QMainWindow>
#include <QNetworkReply>
#include "ui_httpdnsdemo.h"

class HttpDnsDemo : public QMainWindow
{
    Q_OBJECT

public:
    HttpDnsDemo(QWidget *parent = nullptr);
    ~HttpDnsDemo();

private slots:
    void clickbutton();

private:
    Ui::httpdnsdemo ui;
};
