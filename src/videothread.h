#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H
#include <QThread>

class VideoThread : public QThread
{
    Q_OBJECT
public:
    VideoThread();
};

#endif // VIDEOTHREAD_H
