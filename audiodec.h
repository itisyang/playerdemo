#ifndef AUDIODEC_H
#define AUDIODEC_H

#include <QObject>
#include "globalhelper.h"

class AudioDec : public QObject
{
    Q_OBJECT
public:
    explicit AudioDec(QObject *parent = nullptr);

signals:

public slots:
    //由主线程发信号至已使用moveToThread的AudioDec实例，下面的函数在线程中执行
    int OnStartDec();
};

#endif // AUDIODEC_H
