
#pragma once
#include <QObject>
#include <QByteArray>

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(QByteArray data, int statusCode);

public slots:
    void process();  // 线程入口

signals:
    void finished(QString result);  // 发送处理结果给主线程

private:
    QByteArray data_;
    int statusCode_;
};
