#ifndef READTHREAD_H
#define READTHREAD_H
#include <QThread>

//读取文件
class ReadThread : public QThread
{
    Q_OBJECT
public:
    ReadThread();
    ~ReadThread();
    bool StartThread(QString strVideoName);
    bool StopThread();
private:
    void run();
    bool m_bThreadRunning;

    QString m_strVideoName;
};

#endif // READTHREAD_H
