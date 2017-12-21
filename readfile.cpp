#include <QDebug>

#include "readfile.h"
#include "videoctl.h"

ReadFile::ReadFile()
{
    m_pFormatCtx = NULL;
}

void ReadFile::run()
{
    int err, i, ret;
    int nVideoIndex = -1;
    int nAudioIndex = -1;
    int nSubtitleIndex = -1;
    AVFormatContext *ic = NULL;

    qDebug() << "ReadFile Thread ID:" << QThread::currentThreadId();

    if (m_strFilePath.isEmpty())
    {
        return;
    }


    //构建 处理封装格式 结构体
    ic = VideoCtl::GetInstance()->GetAVFormatCtx();
    if (!ic)
    {
        return;
    }

    err = avformat_open_input(&ic, m_strFilePath.toUtf8().data(), NULL, NULL);
    if (err < 0)
    {
        emit SigPlayMsg(m_strFilePath + " open fail, err = " + QString::number(err));
        return;
    }
    if (avformat_find_stream_info(ic, NULL) < 0)
    {
        emit SigPlayMsg("Couldn't find stream information.");
        return ;
    }
    for (i = 0; i< ic->nb_streams; i++)
    {
        if(ic->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO)
        {
            nVideoIndex=i;
        }
        else if(ic->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO)
        {
            nAudioIndex=i;
        }
        else if(ic->streams[i]->codec->codec_type==AVMEDIA_TYPE_SUBTITLE)
        {
            nSubtitleIndex=i;
        }
    }

    emit SigPlayMsg("stream info:" + QString::number(nVideoIndex)
                    + " " + QString::number(nAudioIndex)
                    + " " + QString::number(nSubtitleIndex));

    // 发送解码信号
    if (nVideoIndex >= 0)
    {
        emit SigStartVideoDec();
    }
    if (nAudioIndex >= 0)
    {
        emit SigStartAudioDec();
    }
    if (nSubtitleIndex >= 0)
    {
        emit SigStartSubtitleDec();
    }

    while (m_bRunning)
    {


        break;
    }
}

int ReadFile::StartRead(QString strFilePath)
{
    m_strFilePath = strFilePath;

    StartThread();

    return NoError;
}

int ReadFile::OnStartRead(QString strFilePath)
{
    m_strFilePath = strFilePath;

    StartThread();

    return NoError;
}
