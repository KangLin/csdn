#include "cnumber.h"
#include <QDebug>

CNumber::CNumber()
{
}

int CNumber::Init()
{
    m_StartTime = QDateTime::currentDateTime();
    SetEndTime();
    m_TotalNumber = 0;
    m_LoopNumber = 0;
}

int CNumber::SetEndTime()
{
    m_mutext.lock();
    m_EndTime = QDateTime::currentDateTime();
    m_mutext.unlock();
}

QString CNumber::GetUserTime()
{
    int nSec;
    m_mutext.lock();
    nSec = m_StartTime.secsTo(m_EndTime);
    m_mutext.unlock();
    QTime time(0, 0, 0, 0);
    QTime t = time.addSecs(nSec);
    //qDebug() << "sec:" << nSec;
    return t.toString("hh:mm:ss");
}

CNumber g_Number;
