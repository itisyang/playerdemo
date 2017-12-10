#ifndef READFILE_H
#define READFILE_H

#include <QObject>
#include "customthread.h"
#include "globalhelper.h"

class ReadFile : public CustomThread
{
    Q_OBJECT
public:
    explicit ReadFile();

    void run();

signals:

public slots:
    //由主线程发信号至已使用moveToThread的ReadFile实例，下面的函数在线程中执行
    int OnStartRead(QString strFilePath);
private:
    QString m_strFilePath;
};

#endif // READFILE_H
