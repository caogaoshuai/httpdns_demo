#pragma once
#include <qobject.h>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <QNetworkRequest>
#include "HttpDns.h"
class Worker :public QObject
{
    Q_OBJECT
public:
    Worker() {}

signals:
    void resultReady(const QNetworkRequest req);
public slots:
	void doWork(const QString strurl);
};

