#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H
#include <QThread>

class AudioThread : public QThread
{
    Q_OBJECT
public:
    AudioThread();
};

#endif // AUDIOTHREAD_H
