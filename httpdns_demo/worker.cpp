// Worker.cpp
#include "worker.h"
#include <QThread>

Worker::Worker(QByteArray data, int statusCode)
    : data_(data), statusCode_(statusCode)
{}

void Worker::process()
{
    QThread::sleep(10);  // ºÄÊ±²Ù×÷

    QString result;
   
    result = QString("status code: %1\ncontent:\n%2")
        .arg(statusCode_)
        .arg(QString::fromUtf8(data_));

   

    emit finished(result);
}
