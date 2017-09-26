#ifndef SUBTITLETHREAD_H
#define SUBTITLETHREAD_H
#include <QThread>

class SubtitleThread : public QThread
{
    Q_OBJECT
public:
    SubtitleThread();
};

#endif // SUBTITLETHREAD_H
