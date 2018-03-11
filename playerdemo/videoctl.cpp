/*
 * @file 	videoctl.cpp
 * @date 	2018/01/21 12:15
 *
 * @author 	itisyang
 * @Contact	itisyang@gmail.com
 *
 * @brief 	视频控制类
 * @note
 */

#include <QThread>
#include <QDebug>

#include "videoctl.h"
#include "globalhelper.h"

# pragma execution_character_set("utf-8")

#ifdef _WIN32
#include <windows.h>
#endif


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

    m_pAVFormatContext = avformat_alloc_context();
    if (!m_pAVFormatContext)
    {
        emit SigPlayMsg("Could not allocate context.");
        return false;
    }


    m_bInited = true;

    return true;
}

bool VideoCtl::ConnectSignalSlots()
{
    QList<bool> listRet;
    bool bRet;

    bRet = connect(&m_ReadFile, &ReadFile::SigPlayMsg, this, &VideoCtl::SigPlayMsg);
    listRet.append(bRet);
    bRet = connect(&m_VideoDec, &VideoDec::SigPlayMsg, this, &VideoCtl::SigPlayMsg);
    listRet.append(bRet);
    bRet = connect(&m_AudioDec, &AudioDec::SigPlayMsg, this, &VideoCtl::SigPlayMsg);
    listRet.append(bRet);
    bRet = connect(&m_SubtitleDec, &SubtitleDec::SigPlayMsg, this, &VideoCtl::SigPlayMsg);
    listRet.append(bRet);

    //开始解码信号槽连接
    bRet = connect(&m_ReadFile, &ReadFile::SigStartVideoDec, &m_VideoDec, &VideoDec::OnStartDec);
    listRet.append(bRet);
    bRet = connect(&m_ReadFile, &ReadFile::SigStartAudioDec, &m_AudioDec, &AudioDec::OnStartDec);
    listRet.append(bRet);
    bRet = connect(&m_ReadFile, &ReadFile::SigStartSubtitleDec, &m_SubtitleDec, &SubtitleDec::OnStartDec);
    listRet.append(bRet);

	//开始播放信号
	qRegisterMetaType<WId>("WId");
	bRet = connect(this, &VideoCtl::SigStartPlay, &m_PlayThread, &PlayThread::OnStarPlay);
	listRet.append(bRet);

    bRet = connect(&m_PlayThread, &PlayThread::SigFrameDimensionsChanged, this, &VideoCtl::SigFrameDimensionsChanged);
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
        return nullptr;
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
        //emit SigStartDec();
		//emit SigStartPlay();
    }

    return true;
}


static int lockmgr(void **mtx, enum AVLockOp op)
{
    switch (op) {
    case AV_LOCK_CREATE:
        *mtx = SDL_CreateMutex();
        if (!*mtx) {
            av_log(NULL, AV_LOG_FATAL, "SDL_CreateMutex(): %s\n", SDL_GetError());
            return 1;
        }
        return 0;
    case AV_LOCK_OBTAIN:
        return !!SDL_LockMutex(*mtx);
    case AV_LOCK_RELEASE:
        return !!SDL_UnlockMutex(*mtx);
    case AV_LOCK_DESTROY:
        SDL_DestroyMutex(*mtx);
        return 0;
    }
    return 1;
}
static void do_exit(VideoState *is)
{
    if (is) {
        stream_close(is);
    }
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    av_lockmgr_register(NULL);
    uninit_opts();
#if CONFIG_AVFILTER
    av_freep(&vfilters_list);
#endif
    avformat_network_deinit();
    if (show_status)
        printf("\n");
    SDL_Quit();
    av_log(NULL, AV_LOG_QUIET, "%s", "");
    exit(0);
    }

bool VideoCtl::StartPlay(QString strFileName, WId widPlayWid)
{
# if 0
	if (NoError == m_ReadFile.StartRead(strFileName))
	{
		//emit SigStartDec();
		emit SigStartPlay(widPlayWid);
	}

	return true;
#else
    int flags;
    flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER;
    if (SDL_Init(flags)) {
        av_log(NULL, AV_LOG_FATAL, "Could not initialize SDL - %s\n", SDL_GetError());
        av_log(NULL, AV_LOG_FATAL, "(Did you set the DISPLAY variable?)\n");
        exit(1);
    }
    SDL_EventState(SDL_SYSWMEVENT, SDL_IGNORE);
    SDL_EventState(SDL_USEREVENT, SDL_IGNORE);

    //注册自定义锁
    if (av_lockmgr_register(lockmgr)) {
        av_log(NULL, AV_LOG_FATAL, "Could not initialize lock manager!\n");
        do_exit(1);
    }












    return true;
#endif
}

AVFormatContext *VideoCtl::GetAVFormatCtx()
{
    return m_pAVFormatContext;
}

VideoDataOprator *VideoCtl::GetVideoDataOprator()
{
    return &m_VideoDataOprator;
}

bool VideoCtl::StreamComponentOpen(AVFormatContext *ic, int nVideoStreamIndex, int nAudioStreamIndex, int nSubtitleStreamIndex)
{
    AVCodecContext *avctx = nullptr;
    AVCodec *codec;

    qDebug() << "StreamComponentOpen" << nVideoStreamIndex << nAudioStreamIndex << nSubtitleStreamIndex;
    if (nVideoStreamIndex >= 0)
    {
        //初始化结构体
        avctx = avcodec_alloc_context3(nullptr);
        if (!avctx)
        {
            return false;
        }
//         avformat_match_stream_specifier
//         av_find_best_stream
        avcodec_parameters_to_context(avctx, ic->streams[nVideoStreamIndex]->codecpar);
        av_codec_set_pkt_timebase(avctx, ic->streams[nVideoStreamIndex]->time_base);
        //寻找解码器
        codec = avcodec_find_decoder(avctx->codec_id);
        avcodec_open2(avctx, codec, nullptr);

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

