#include "VideoCtl.h"
#include <QThread>
#include <QDebug>

# pragma execution_character_set("utf-8")

const QString VideoCtl::strProgrameBirthYear = "2017";

VideoCtl::VideoCtl(QObject *parent) : QObject(parent)
{
    m_bInited = false;
    m_pAVFormatContext = nullptr;

#if CONFIG_AVDEVICE
    //注册所有设备
    avdevice_register_all();
#endif
#if CONFIG_AVFILTER
    //注册所有过滤器
    avfilter_register_all();
#endif
    //注册所有复用器、编码器
    av_register_all();
    //网络格式初始化
    avformat_network_init();


}

bool VideoCtl::Init()
{
    if (m_bInited == true)
    {
        return true;
    }

    if (ConnectSignalSlots() == false)
    {
        return false;
    }

    m_bInited = true;

    return true;
}

bool VideoCtl::ConnectSignalSlots()
{
    QList<bool> listRet;
    bool bRet;

    //错误信息信号槽连接
    //bRet = connect(this, SIGNAL(SigPlayMsg(QString)), SLOT(OnPlayMsg(QString)));
    //listRet.append(bRet);
    bRet = connect(&m_ReadFile, SIGNAL(SigPlayMsg(QString)), this, SIGNAL(SigPlayMsg(QString)));
    listRet.append(bRet);
    bRet = connect(&m_VideoDec, SIGNAL(SigPlayMsg(QString)), this, SIGNAL(SigPlayMsg(QString)));
    listRet.append(bRet);
    bRet = connect(&m_AudioDec, SIGNAL(SigPlayMsg(QString)), this, SIGNAL(SigPlayMsg(QString)));
    listRet.append(bRet);
    bRet = connect(&m_SubtitleDec, SIGNAL(SigPlayMsg(QString)), this, SIGNAL(SigPlayMsg(QString)));
    listRet.append(bRet);

    //开始解码信号槽连接
    bRet = connect(this, SIGNAL(SigStartDec()), &m_VideoDec, SLOT(OnStartDec()));
    listRet.append(bRet);
    bRet = connect(this, SIGNAL(SigStartDec()), &m_AudioDec, SLOT(OnStartDec()));
    listRet.append(bRet);
    bRet = connect(this, SIGNAL(SigStartDec()), &m_SubtitleDec, SLOT(OnStartDec()));
    listRet.append(bRet);
	qRegisterMetaType<QPixmap>("QPixmap&");
	bRet = connect(&m_VideoDec, SIGNAL(SigImage(QPixmap&)), this, SIGNAL(SigImage(QPixmap&)));
	listRet.append(bRet);
	

    for (bool bReturn : listRet)
    {
        if (bReturn == false)
        {
            return false;
        }
    }

    return true;
}

VideoCtl *VideoCtl::m_pInstance = new VideoCtl();

VideoCtl *VideoCtl::GetInstance()
{
    if (false == m_pInstance->Init())
    {
        return NULL;
    }
    return m_pInstance;
}

void VideoCtl::ReleaseInstance()
{

}

bool VideoCtl::StartPlay(QString strFileName)
{
    qDebug() << "VideoCtl Thread ID:" << QThread::currentThreadId();

    if (NoError == m_ReadFile.StartRead(strFileName))
    {
        emit SigStartDec();
    }

    return true;
}

AVFormatContext *VideoCtl::GetAVFormatCtx()
{
    if (m_pAVFormatContext == nullptr)
    {
        m_pAVFormatContext = avformat_alloc_context();
        if (!m_pAVFormatContext)
        {
            emit SigPlayMsg("Could not allocate context.");
        }
    }

    return m_pAVFormatContext;
}

VideoDataOprator *VideoCtl::GetVideoDataOprator()
{
    return &m_VideoDataOprator;
}

bool VideoCtl::StreamComponentOpen(int nVideoStreamIndex, int nAudioStreamIndex, int nSubtitleStreamIndex)
{
    AVFormatContext *ic = VideoCtl::GetInstance()->GetAVFormatCtx();
    AVCodecContext *avctx;
    AVCodec *codec;

    if (nVideoStreamIndex >= 0)
    {
        //初始化结构体
        avctx = avcodec_alloc_context3(NULL);
        if (!avctx)
            return false;
        avcodec_parameters_to_context(avctx, ic->streams[nVideoStreamIndex]->codecpar);
        av_codec_set_pkt_timebase(avctx, ic->streams[nVideoStreamIndex]->time_base);
        //寻找解码器
        codec = avcodec_find_decoder(avctx->codec_id);
        avcodec_open2(avctx, codec, NULL);

        m_VideoDec.video_stream = nVideoStreamIndex;
        m_VideoDec.video_st = ic->streams[nVideoStreamIndex];
        m_VideoDec.video_avctx = avctx;
    }

    return true;
}

void VideoCtl::OnPlayMsg(QString strMsg)
{
    qDebug() << strMsg;
}

