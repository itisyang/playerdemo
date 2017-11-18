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

    const int m_nMaxNumFrameCache;//缓存帧数

    // V-Video  A-Audio S-Subtitle
    //解码前
    QMutex m_mutexV;
    QMutex m_mutexA;
    QMutex m_mutexS;
    QList<AVPacket*> m_listV;
    QList<AVPacket*> m_listA;
    QList<AVPacket*> m_listS;
    //解码后
    QMutex m_mutexVDec;
    QMutex m_mutexADec;
    QMutex m_mutexSDec;
    QList<AVFrame*> m_ListVDec;
    QList<AVFrame*> m_ListADec;
    QList<AVFrame*> m_ListSDec;

};

#endif // VIDEODATAOPRATOR_H
