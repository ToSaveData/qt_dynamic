#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDateTime>
#include <QFile>
#include <QDebug>

class Downloader : public QObject
{
    Q_OBJECT
public:
    Downloader(QObject *parent = 0);
public slots:
    void replyFinished(QNetworkReply *reply);
private:
    QNetworkAccessManager *manager;
};

#endif // DOWNLOADER_H
