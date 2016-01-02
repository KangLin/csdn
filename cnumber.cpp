#include "cnumber.h"

CNumber::CNumber()
{
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
    QTime time;
    time.addSecs(nSec);
    return time.toString();
}

CNumber g_Number;
