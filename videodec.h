#ifndef VIDEODEC_H
#define VIDEODEC_H

#include <QObject>
#include "globalhelper.h"

class VideoDec : public QObject
{
    Q_OBJECT
public:
    explicit VideoDec(QObject *parent = nullptr);

signals:

public slots:
    //由主线程发信号至已使用moveToThread的VideoDec实例，下面的函数在线程中执行
    int OnStartDec();
};

#endif // VIDEODEC_H
