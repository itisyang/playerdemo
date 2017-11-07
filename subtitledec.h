#ifndef SUBTITLEDEC_H
#define SUBTITLEDEC_H

#include <QObject>
#include "globalhelper.h"

class SubtitleDec : public QObject
{
    Q_OBJECT
public:
    explicit SubtitleDec(QObject *parent = nullptr);

signals:

public slots:
    //由主线程发信号至已使用moveToThread的SubtitleDec实例，下面的函数在线程中执行
    int OnStartDec();
};

#endif // SUBTITLEDEC_H
