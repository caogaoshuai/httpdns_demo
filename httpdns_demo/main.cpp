#include "HttpDnsDemo.h"
#include "HttpDns.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HttpDnsSetup(false);
    HttpDnsDemo w;
    w.show();
    a.exec();
    HttpDnsCleanup();
    return 1;
}
