#ifndef CDOWNLOAD_H
#define CDOWNLOAD_H

#include <QString>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <thread>
#include <vector>
#include "curl/curl.h"

class CDownLoad : public QObject
{
    Q_OBJECT
public:
    CDownLoad(QObject *parent = NULL);
    ~CDownLoad();
    
    int OnWork(int nLoopNumber);

private:
    std::vector<QString> m_vUrl;

public:
    int DownLoad(QString szUrl);
};

#endif // CDOWNLOAD_H
