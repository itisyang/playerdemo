#include <QDebug>
#include <QTime>
#include "readfile.h"
#include "videoctl.h"

# pragma execution_character_set("utf-8")

ReadFile::ReadFile()
{
    m_pFormatCtx = nullptr;
}

void ReadFile::run()
{
    int err, i, ret;

    AVFormatContext *ic = nullptr;

    AVPacket pkt1, *pkt = &pkt1;

    int st_index[AVMEDIA_TYPE_NB];

    qDebug() << sizeof(st_index);
    memset(st_index, -1, sizeof(st_index));

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
	
    err = avformat_open_input(&ic, m_strFilePath.toUtf8().data(), nullptr, nullptr);
    if (err < 0)
    {
        emit SigPlayMsg(m_strFilePath + " open fail, err = " + QString::number(err));
		char buf[1024];
		av_strerror(err, buf, 1024);
		qDebug() << buf;
        return;
    }
    av_format_inject_global_side_data(ic);

    if (avformat_find_stream_info(ic, nullptr) < 0)
    {
        emit SigPlayMsg("Couldn't find stream information.");
        return ;
    }

    //获得视频、音频、字幕的流索引
    st_index[AVMEDIA_TYPE_VIDEO] =
        av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO,
            st_index[AVMEDIA_TYPE_VIDEO], -1, NULL, 0);
    st_index[AVMEDIA_TYPE_AUDIO] =
        av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO,
            st_index[AVMEDIA_TYPE_AUDIO],
            st_index[AVMEDIA_TYPE_VIDEO],
            NULL, 0);
    st_index[AVMEDIA_TYPE_SUBTITLE] =
        av_find_best_stream(ic, AVMEDIA_TYPE_SUBTITLE,
            st_index[AVMEDIA_TYPE_SUBTITLE],
            (st_index[AVMEDIA_TYPE_AUDIO] >= 0 ?
                st_index[AVMEDIA_TYPE_AUDIO] :
                st_index[AVMEDIA_TYPE_VIDEO]),
            NULL, 0);


    emit SigPlayMsg("stream info:" + QString::number(st_index[AVMEDIA_TYPE_VIDEO])
                    + " " + QString::number(st_index[AVMEDIA_TYPE_AUDIO])
                    + " " + QString::number(st_index[AVMEDIA_TYPE_SUBTITLE]));

    VideoCtl::GetInstance()->StreamComponentOpen(st_index[AVMEDIA_TYPE_VIDEO], 
        st_index[AVMEDIA_TYPE_AUDIO], 
        st_index[AVMEDIA_TYPE_SUBTITLE]);
    // 发送解码信号
    if (st_index[AVMEDIA_TYPE_VIDEO] >= 0)
    {
        emit SigStartVideoDec();
    }
    if (st_index[AVMEDIA_TYPE_AUDIO] >= 0)
    {
        emit SigStartAudioDec();
    }
    if (st_index[AVMEDIA_TYPE_SUBTITLE] >= 0)
    {
        emit SigStartSubtitleDec();
    }

	VideoDataOprator *pVideoDataOprator = VideoCtl::GetInstance()->GetVideoDataOprator();

    while (m_bRunning)
    {
// 		QTime t;
// 		t.start();

        //按帧读取
        ret = av_read_frame(ic, pkt);
        if (ret < 0)
        {
            break;
        }

        //按数据帧的类型存放至对应队列
        if (pkt->stream_index == st_index[AVMEDIA_TYPE_VIDEO]) {
			while (1)
			{
				if (pVideoDataOprator->PutAVPacketData(pkt, VIDEO_DATA) == true)
				{
					//qDebug() << "读取一帧";
					break;
				}
				else
				{
					msleep(10);
				}
			}
            
            //emit SigPlayMsg("一帧");
//        } else if (pkt->stream_index == nAudioIndex) {
//            pVideoDataOprator->PutAVPacketData(pkt, AUDIO_DATA);
//        } else if (pkt->stream_index == nSubtitleIndex) {
//            pVideoDataOprator->PutAVPacketData(pkt, SUBTITLE_DATA);
        } else {
            av_packet_unref(pkt);
        }

		//qDebug("读取一帧消耗: %d ms", t.elapsed());
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
