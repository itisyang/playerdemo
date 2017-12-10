#ifndef AUDIODEC_H
#define AUDIODEC_H

#include <QObject>
#include "globalhelper.h"
#include "customthread.h"
class AudioDec : public CustomThread
{
    Q_OBJECT
public:
    explicit AudioDec();

    void run();

signals:

public slots:
    //由主线程发信号至已使用moveToThread的AudioDec实例，下面的函数在线程中执行
    int OnStartDec();
};

#endif // AUDIODEC_H
