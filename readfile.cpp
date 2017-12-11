#include "readfile.h"
#include <QDebug>
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

    qDebug() << "VideoCtl Thread ID:" << QThread::currentThreadId();

    if (m_strFilePath.isEmpty())
    {
        return;
    }
    if (m_pFormatCtx)
    {
        avformat_free_context(m_pFormatCtx);
        m_pFormatCtx = NULL;
    }
    //构建 处理封装格式 结构体
    m_pFormatCtx = avformat_alloc_context();
    if (!m_pFormatCtx)
    {
        emit SigPlayMsg("Could not allocate context.");
        return;
    }

    err = avformat_open_input(&m_pFormatCtx, m_strFilePath.toUtf8().data(), NULL, NULL);
    if (err < 0)
    {
        emit SigPlayMsg(m_strFilePath + " open fail, err = " + QString::number(err));
        return;
    }
    if (avformat_find_stream_info(m_pFormatCtx, NULL) < 0)
    {
        emit SigPlayMsg("Couldn't find stream information.");
        return ;
    }
    for (i = 0; i<m_pFormatCtx->nb_streams; i++)
    {
        if(m_pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO)
        {
            nVideoIndex=i;
        }
        else if(m_pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO)
        {
            nAudioIndex=i;
        }
        else if(m_pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_SUBTITLE)
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

    }
    if (nAudioIndex >= 0)
    {

    }
    if (nSubtitleIndex >= 0)
    {

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
