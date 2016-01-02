#ifndef CNUBER_H
#define CNUBER_H
#include <QAtomicInt>

class CNumber
{
public:
    CNumber();

    QAtomicInt m_LoopNumber;
    QAtomicInt m_TotalNumber;
};

#endif // CNUBER_H
