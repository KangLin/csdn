#include "cdownload.h"
#include <QDebug>
#include <QUrl>
#include <QFile>
#include <QApplication>
#include <QThread>

CDownLoad::CDownLoad(QObject *parent): QObject(parent)
{
}

CDownLoad::~CDownLoad()
{
}

int CDownLoad::OnWork()
{
    qDebug() << "CDownLoad::OnWork";
    QString szFile = qApp->applicationDirPath() + "/files.txt";
    QFile f(szFile);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Don't open file:" << szFile;
        return -1;
    }
    while (!f.atEnd()) {
        QByteArray line = f.readLine();
        QString szUrl(line);
        if(szUrl.right(1) == "\n")
            szUrl = szUrl.left(szUrl.length() -1);
        m_vUrl.push_back(szUrl);
    }

    std::vector<QString>::iterator it;
    for(it = m_vUrl.begin(); it != m_vUrl.end(); it++)
    {
        DownLoad(*it);
    }
    
}

static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream)
{
    return  size * nmemb;
}

int CDownLoad::DownLoad(QString szUrl)
{
    CURL *curl;
    CURLcode res;
    
    curl = curl_easy_init();
    if(curl) {
        /*
         * You better replace the URL with one that works!
         */ 
        curl_easy_setopt(curl, CURLOPT_URL,
                         szUrl.toStdString().c_str());
        /* Define our callback to get called when there's data to be written */ 
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
        /* Set a pointer to our struct to pass to the callback */ 
        // curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
        
        /* Switch on full protocol/debug output */ 
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        
        res = curl_easy_perform(curl);
        
        /* always cleanup */ 
        curl_easy_cleanup(curl);
        
    }
}
