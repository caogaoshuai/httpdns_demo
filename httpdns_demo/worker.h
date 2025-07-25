// worker.h

#pragma once

#include <QObject>
#include <QUrl>

class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(const QUrl& url, QObject* parent = nullptr);
    ~Worker() {}

public slots:
    void process();

signals:
    void finished(const QString& result);

private:
    QUrl url_;
};
