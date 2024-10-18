#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_httpdnsdemo.h"

class HttpDnsDemo : public QMainWindow
{
    Q_OBJECT

public:
    HttpDnsDemo(QWidget *parent = nullptr);
    ~HttpDnsDemo();

    void clickbutton();
private:
    Ui::httpdnsdemo ui;
};
