#ifndef VIDEOCTL_H
#define VIDEOCTL_H

#include <QObject>
#include <QThread>

#include "globalhelper.h"

#include "SDL.h"
#include "SDL_thread.h"

#include "readfile.h"
#include "videodec.h"
#include "audiodec.h"
#include "subtitledec.h"

//单例模式
class VideoCtl : public QObject
{
    Q_OBJECT

public:
    //explicit VideoCtl(QObject *parent = nullptr);

    static VideoCtl* GetInstance();
    static VideoCtl* ReleaseInstance();
signals:

public slots:

private:
    explicit VideoCtl(QObject *parent = nullptr);
    static VideoCtl* m_pInstance;

    QThread ReadFileThread;//读取文件线程
    QThread VideoDecThread;//视频解码线程
    QThread AudioDecThread;//音频解码线程
    QThread SubtitleDecThread;//字幕解码线程



    static const QString strProgrameBirthYear;//程序初始创建年

};

#endif // VIDEOCTL_H
