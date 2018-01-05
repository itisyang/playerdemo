#ifndef GLOBALHELPER_H
#define GLOBALHELPER_H

# pragma execution_character_set("utf-8")

enum ERROR_CODE
{
    NoError = 0,
    ErrorFileInvalid
};

enum DATA_TYPE
{
    VIDEO_DATA = 0,
    AUDIO_DATA,
    SUBTITLE_DATA
};


#include <QString>
#include <QPushButton>

class GlobalHelper
{
public:
    GlobalHelper();
    static QString GetQssStr(QString strQssPath);
    static void    SetIcon(QPushButton* btn, int iconSize, QChar icon);
};

//必须加以下内容,否则编译不能通过,为了兼容C和C99标准
#ifndef INT64_C
#define INT64_C
#define UINT64_C
#endif

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


#endif // GLOBALHELPER_H
