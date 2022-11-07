#include "downloader.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Downloader d;
    return a.exec();
}
