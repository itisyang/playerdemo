#ifndef CUSTOMTHREAD_H
#define CUSTOMTHREAD_H

#include <QThread>

class CustomThread : public QThread
{
public:
    CustomThread();
    ~CustomThread();

    bool StartThread();
    bool StopThread();

protected:
    bool m_bRunning;
};

#endif // CUSTOMTHREAD_H
