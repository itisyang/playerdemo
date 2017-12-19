/**
 * @file
 * @brief   视频解码
 * @author  itisyang
 * @date
 * @note
 */

#ifndef VIDEODEC_H
#define VIDEODEC_H

#include <QObject>
#include "globalhelper.h"
#include "customthread.h"

class VideoDec : public CustomThread
{
    Q_OBJECT
public:
    explicit VideoDec();

    void run();

signals:

public slots:
    //由主线程发信号至已使用moveToThread的VideoDec实例，下面的函数在线程中执行
    void OnStartDec();


};

#endif // VIDEODEC_H
