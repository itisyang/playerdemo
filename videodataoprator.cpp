#include "videodataoprator.h"

VideoDataOprator::VideoDataOprator(QObject *parent) : QObject(parent),
  MaxNumFrameCache(10)
{

}
//存放原始数据
bool VideoDataOprator::PutData(AVPacket *pkt, DATA_TYPE type)
{
    switch (type) {
    case VIDEO_DATA:
        PutDataVideo(pkt);
        break;
    case AUDIO_DATA:
        PutDataAudio(pkt);
        break;
    case SUBTITLE_DATA:
        PutDataSubtitle(pkt);
        break;
    default:
        break;
    }

    return true;
}
//获取原始数据
bool VideoDataOprator::GetData(AVPacket *pkt, DATA_TYPE type)
{
    switch (type) {
    case VIDEO_DATA:
        GetDataVideo(pkt);
        break;
    case AUDIO_DATA:
        GetDataAudio(pkt);
        break;
    case SUBTITLE_DATA:
        GetDataSubtitle(pkt);
        break;
    default:
        break;
    }

    return true;
}
//存放解码数据
bool VideoDataOprator::PutDataDec(AVFrame *frame, DATA_TYPE type)
{
    switch (type) {
    case VIDEO_DATA:
        PutDataDecVideo(frame);
        break;
    case AUDIO_DATA:
        PutDataDecAudio(frame);
        break;
    case SUBTITLE_DATA:
        PutDataDecSubtitle(frame);
        break;
    default:
        break;
    }

    return true;
}
//获取解码数据
bool VideoDataOprator::GetDataDec(AVFrame *frame, DATA_TYPE type)
{
    switch (type) {
    case VIDEO_DATA:
        GetDataDecVideo(frame);
        break;
    case AUDIO_DATA:
        GetDataDecAudio(frame);
        break;
    case SUBTITLE_DATA:
        GetDataDecSubtitle(frame);
        break;
    default:
        break;
    }

    return true;
}

bool VideoDataOprator::PutDataVideo(AVPacket *pkt)
{

}

bool VideoDataOprator::GetDataVideo(AVPacket *pkt)
{

}

bool VideoDataOprator::PutDataDecVideo(AVFrame *frame)
{

}

bool VideoDataOprator::GetDataDecVideo(AVFrame *frame)
{

}

bool VideoDataOprator::PutDataAudio(AVPacket *pkt)
{

}

bool VideoDataOprator::GetDataAudio(AVPacket *pkt)
{

}

bool VideoDataOprator::PutDataDecAudio(AVFrame *frame)
{

}

bool VideoDataOprator::GetDataDecAudio(AVFrame *frame)
{

}

bool VideoDataOprator::PutDataSubtitle(AVPacket *pkt)
{

}

bool VideoDataOprator::GetDataSubtitle(AVPacket *pkt)
{

}

bool VideoDataOprator::PutDataDecSubtitle(AVFrame *frame)
{

}

bool VideoDataOprator::GetDataDecSubtitle(AVFrame *frame)
{

}
