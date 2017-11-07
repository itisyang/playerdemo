#ifndef READFILE_H
#define READFILE_H

#include <QObject>
#include "globalhelper.h"

class ReadFile : public QObject
{
    Q_OBJECT
public:
    explicit ReadFile(QObject *parent = nullptr);

signals:

public slots:
    //由主线程发信号至已使用moveToThread的ReadFile实例，下面的函数在线程中执行
    int OnStartRead(QString strFileName);
};

#endif // READFILE_H
