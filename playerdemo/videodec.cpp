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

		AVFrame *frame = av_frame_alloc();
        memset(frame, 0, sizeof(AVFrame));
        avcodec_decode_video2(video_avctx, frame, &got_frame, &pkt);

        //qDebug() << "初始化图片空间";
        AVFrame *picture = av_frame_alloc();

		int nWidth = frame->width;
		int nHeight = frame->height;

		if (nWidth == 0 || nHeight == 0)
		{
			continue;
		}


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

		//图像缩放规则
		SwsContext *pSwsContext = NULL;
		pSwsContext = sws_getContext(nWidth, nHeight, AV_PIX_FMT_YUV420P,
			nWidth, nHeight, AV_PIX_FMT_RGB24,
			SWS_BICUBIC, 0, 0, 0);

		//第一个参数为sws_getContext函数返回的值
		//第四个参数为从输入图像数据的第多少列开始逐行扫描，通常设为0
		//第五个参数为需要扫描多少行，通常为输入图像数据的高度
		ret = sws_scale(pSwsContext, (const uint8_t* const *)frame->data,
			frame->linesize, 0, nHeight, picture->data, picture->linesize);

		av_frame_free(&frame);


        QImage* image = new QImage(picture->data[0],
			nWidth, nHeight, QImage::Format_RGB888);

		av_frame_free(&picture);

		QPixmap pix = QPixmap::fromImage(*image);
		emit SigImage(pix);
		//emit SigPlayMsg("发送一帧");

		delete image;
		image = NULL;
		delete out_buffer;
		out_buffer = NULL;

        
		//qDebug() << video_avctx->framerate.num << video_avctx->framerate.den;
		msleep(1000/(video_avctx->framerate.num/ video_avctx->framerate.den));
//        qDebug() << "VideoDec Thread ID:" << QThread::currentThreadId();
//        break;
    }
}

void VideoDec::OnStartDec()
{
    StartThread();
}
