#include <QDebug>
#include <QTime>
#include "readfile.h"
#include "videoctl.h"

# pragma execution_character_set("utf-8")

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

    AVPacket pkt1, *pkt = &pkt1;

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

    VideoCtl::GetInstance()->StreamComponentOpen(nVideoIndex, nAudioIndex, nSubtitleIndex);
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

	VideoDataOprator *pVideoDataOprator = VideoCtl::GetInstance()->GetVideoDataOprator();

    while (m_bRunning)
    {
		QTime t;
		t.start();

        //按帧读取
        ret = av_read_frame(ic, pkt);
        if (ret < 0)
        {
            break;
        }

        //按数据帧的类型存放至对应队列
        if (pkt->stream_index == nVideoIndex) {
			while (1)
			{
				if (pVideoDataOprator->PutData(pkt, VIDEO_DATA) == true)
				{
					//qDebug() << "读取一帧";
					break;
				}
				else
				{
					usleep(1000 * 500);
				}
			}
            
            //emit SigPlayMsg("一帧");
//        } else if (pkt->stream_index == nAudioIndex) {
//            pVideoDataOprator->PutData(pkt, AUDIO_DATA);
//        } else if (pkt->stream_index == nSubtitleIndex) {
//            pVideoDataOprator->PutData(pkt, SUBTITLE_DATA);
        } else {
            av_packet_unref(pkt);
        }

		qDebug("读取一帧消耗: %d ms", t.elapsed());
        //break;
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
