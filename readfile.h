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

    int  StartRead(QString strFilePath);
signals:
    void SigPlayMsg(QString strMsg);
public slots:
    int OnStartRead(QString strFilePath);
private:
    QString m_strFilePath;
    AVFormatContext *m_pFormatCtx;
};

#endif // READFILE_H
