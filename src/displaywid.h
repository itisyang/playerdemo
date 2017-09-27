#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>

//必须加以下内容,否则编译不能通过,为了兼容C和C99标准
#ifndef INT64_C
#define INT64_C
#define UINT64_C
#endif
//引入ffmpeg头文件
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavfilter/avfilter.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/frame.h"
#include "libavutil/pixfmt.h"
#include "libavdevice/avdevice.h"
}

#include "readthread.h"

namespace Ui {
class DisplayWid;
}

class DisplayWid : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayWid(QWidget *parent = 0);
    ~DisplayWid();

protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
private:
    bool InitFFmpeg();

    ReadThread m_threadReadThread;

private:
    Ui::DisplayWid *ui;
};

#endif // DISPLAY_H
