#include <QDebug>
#include "videodec.h"
#include "videoctl.h"
#include "videodataoprator.h"

# pragma execution_character_set("utf-8")

VideoDec::VideoDec()
{

}

void VideoDec::run()
{
    int ret;
    int got_frame = 0;
    AVFrame *frame = av_frame_alloc();

    AVFormatContext *ic = VideoCtl::GetInstance()->GetAVFormatCtx();
    VideoDataOprator *pVideoDataOprator = VideoCtl::GetInstance()->GetVideoDataOprator();

//    AVRational tb = video_st->time_base;
//    AVRational frame_rate = av_guess_frame_rate(ic, video_st, NULL);

    while (m_bRunning)
    {
        AVPacket pkt;
        if (pVideoDataOprator->GetData(pkt, VIDEO_DATA) == false)
        {
            msleep(500);
            continue;
        }
        memset(frame, 0, sizeof(AVFrame));
        avcodec_decode_video2(video_avctx, frame, &got_frame, &pkt);

        qDebug() << "初始化图片空间";
        AVFrame *picture = av_frame_alloc();

		int nWidth = video_avctx->width;
		int nHeight = video_avctx->height;
		uint8_t *out_buffer = NULL;
		try
		{
			out_buffer = new uint8_t[av_image_get_buffer_size(AV_PIX_FMT_RGB24,
				nWidth, nHeight, 1)];
		}
		catch (const std::exception& e)
		{
			qDebug() << e.what();
			return;
		}

        ret = av_image_fill_arrays(picture->data, picture->linesize,
                             out_buffer, AV_PIX_FMT_RGB24, nWidth, nHeight, 1);

        SwsContext *pSwsContext = NULL;
        pSwsContext = sws_getContext(nWidth, nHeight, AV_PIX_FMT_YUV420P,
			nWidth, nHeight, AV_PIX_FMT_RGB24,
                                     SWS_BICUBIC, 0, 0, 0);

        ret = sws_scale(pSwsContext,(const uint8_t* const *)frame->data,
			frame->linesize, 0, nHeight, picture->data, picture->linesize);

        QImage* image = new QImage(picture->data[0],
			nWidth, nHeight, QImage::Format_RGB888);

		QPixmap pix = QPixmap::fromImage(*image);
		//.scaled(ui->label->width(),
		//ui->label->height(),
		//	Qt::KeepAspectRatio,
		//	Qt::SmoothTransformation);
        emit SigImage(pix);
        msleep(500);
//        qDebug() << "VideoDec Thread ID:" << QThread::currentThreadId();
//        break;
    }
}

void VideoDec::OnStartDec()
{
    StartThread();
}
