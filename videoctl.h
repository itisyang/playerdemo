#ifndef VIDEOCTL_H
#define VIDEOCTL_H

#include <QObject>
extern "C"{
#include "libavutil/avstring.h"
#include "libavutil/eval.h"
#include "libavutil/mathematics.h"
#include "libavutil/pixdesc.h"
#include "libavutil/imgutils.h"
#include "libavutil/dict.h"
#include "libavutil/parseutils.h"
#include "libavutil/samplefmt.h"
#include "libavutil/avassert.h"
#include "libavutil/time.h"
#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"
#include "libswscale/swscale.h"
#include "libavutil/opt.h"
#include "libavcodec/avfft.h"
#include "libswresample/swresample.h"
}
#include "SDL.h"
#include "SDL_thread.h"

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


    static const QString strProgrameBirthYear;//程序初始创建年

};

#endif // VIDEOCTL_H
