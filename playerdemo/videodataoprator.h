/*
 * @file 	videodataoprator.h
 * @date 	2018/01/07 10:57
 *
 * @author 	itisyang
 * @Contact	itisyang@gmail.com
 *
 * @brief 	数据管理线程（视频、音频、字幕）
 * @note
 */

#ifndef VIDEODATAOPRATOR_H
#define VIDEODATAOPRATOR_H

#include <QObject>
#include <QMutex>
#include <QByteArray>
#include <QWaitCondition> 
#include "globalhelper.h"


#define VIDEO_PICTURE_QUEUE_SIZE 3
#define SUBPICTURE_QUEUE_SIZE 16
#define SAMPLE_QUEUE_SIZE 9
#define FRAME_QUEUE_SIZE FFMAX(SAMPLE_QUEUE_SIZE, FFMAX(VIDEO_PICTURE_QUEUE_SIZE, SUBPICTURE_QUEUE_SIZE))


class VideoDataOprator : public QObject
{
    Q_OBJECT
public:
    explicit VideoDataOprator(QObject *parent = nullptr);


	/**
	 * @brief	初始化
	 * 
	 * @param	
	 * @return	
	 * @note 	
	 */

	bool Init();

	/**
	 * @brief	存放原始数据
	 * 
	 * @param	pkt	数据包
	 * @param	type 数据包类型
	 * @return	true 成功 false 失败
	 * @note 	
	 */
    bool PutAVPacketData(AVPacket* pkt, DATA_TYPE type);
	/**
	 * @brief	获取原始数据
	 * 
	 * @param	pkt	数据包
	 * @param	type 数据包类型
	 * @return	true 成功 false 失败
	 * @note 	
	 */
    bool GetAVPacketData(AVPacket& pkt, DATA_TYPE type);
	/**
	 * @brief	存放解码数据
	 * 
	 * @param	frame 解码数据帧
	 * @param	type 数据类型
	 * @return	true 成功 false 失败
	 * @note 	
	 */
    bool PutAVFrameData(AVFrame* frame, DATA_TYPE type);
	/**
	 * @brief	获取解码数据
	 * 
	 * @param	frame 解码数据帧
	 * @param	type 数据类型
	 * @return	true 成功 false 失败
	 * @note 	
	 */
    bool GetAVFrameData(AVFrame& frame, DATA_TYPE type);

signals:

public slots:
private:

private:

    const int m_nMaxNumFrameCache;//缓存帧数

    // V-Video  A-Audio S-Subtitle
    //解码前
    QMutex m_mutexAVPacketV;
    QWaitCondition m_condAVPacketV;
    QMutex m_mutexA;
    QMutex m_mutexS;
	QVector<AVPacket*> m_VectorAVPacketV;

    QList<AVPacket*> m_listAVPacketV;
    QList<AVPacket> m_listA;
    QList<AVPacket> m_listS;
    //解码后
    QMutex m_mutexAVFrameV;
    QWaitCondition m_condAVFrameV;
    QMutex m_mutexADec;
    QMutex m_mutexSDec;
    QList<AVFrame*> m_ListAVFrameV;
    QList<AVFrame> m_ListADec;
    QList<AVFrame> m_ListSDec;

};

#endif // VIDEODATAOPRATOR_H
