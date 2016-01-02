#ifndef CNUBER_H
#define CNUBER_H
#include <QAtomicInt>
#include <QDateTime>
#include <QMutex>

class CNumber
{
public:
    CNumber();

     int Init();
     int SetEndTime();
     QString GetUserTime();
     
    QAtomicInt m_LoopNumber;
    QAtomicInt m_TotalNumber;
    QDateTime m_StartTime;

private:
    QMutex m_mutext;
    QDateTime m_EndTime;
};

#endif // CNUBER_H
