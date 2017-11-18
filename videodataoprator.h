#ifndef VIDEODATAOPRATOR_H
#define VIDEODATAOPRATOR_H

#include <QObject>
#include <QMutex>
#include <QByteArray>
#include "globalhelper.h"

class VideoDataOprator : public QObject
{
    Q_OBJECT
public:
    explicit VideoDataOprator(QObject *parent = nullptr);

    bool PutData(AVPacket* pkt, DATA_TYPE type);//存放原始数据
    bool GetData(AVPacket* pkt, DATA_TYPE type);//获取原始数据
    bool PutDataDec(AVFrame* frame, DATA_TYPE type);//存放解码数据
    bool GetDataDec(AVFrame* frame, DATA_TYPE type);//获取解码数据

signals:

public slots:
private:
    bool PutDataVideo(AVPacket* pkt);
    bool GetDataVideo(AVPacket* pkt);
    bool PutDataDecVideo(AVFrame* frame);
    bool GetDataDecVideo(AVFrame* frame);

    bool PutDataAudio(AVPacket* pkt);
    bool GetDataAudio(AVPacket* pkt);
    bool PutDataDecAudio(AVFrame* frame);
    bool GetDataDecAudio(AVFrame* frame);

    bool PutDataSubtitle(AVPacket* pkt);
    bool GetDataSubtitle(AVPacket* pkt);
    bool PutDataDecSubtitle(AVFrame* frame);
    bool GetDataDecSubtitle(AVFrame* frame);
private:

    const int MaxNumFrameCache;//缓存帧数

    //解码前
    QMutex m_mutexVideo;
    QMutex m_mutexAudio;
    QMutex m_mutexSubtitle;
    QList<AVPacket> m_listVideo;
    QList<AVPacket> m_listAudio;
    QList<AVPacket> m_listSubtitle;
    //解码后
    QMutex m_mutexPic;
    QMutex m_mutexSam;
    QMutex m_mutexSub;
    QList<AVFrame> m_ListPic;
    QList<AVFrame> m_ListSam;
    QList<AVFrame> m_ListSub;

};

#endif // VIDEODATAOPRATOR_H
