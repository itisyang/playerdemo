/*
 * @file 	videoctl.h
 * @date 	2018/01/07 10:48
 *
 * @author 	itisyang
 * @Contact	itisyang@gmail.com
 *
 * @brief 	视频控制类
 * @note
 */
#ifndef VIDEOCTL_H
#define VIDEOCTL_H

#include <QObject>
#include <QThread>
#include <QString>

#include "globalhelper.h"


#define MAX_QUEUE_SIZE (15 * 1024 * 1024)
#define MIN_FRAMES 25
#define EXTERNAL_CLOCK_MIN_FRAMES 2
#define EXTERNAL_CLOCK_MAX_FRAMES 10

 /* Minimum SDL audio buffer size, in samples. */
#define SDL_AUDIO_MIN_BUFFER_SIZE 512
 /* Calculate actual buffer size keeping in mind not cause too frequent audio callbacks */
#define SDL_AUDIO_MAX_CALLBACKS_PER_SEC 30

 /* Step size for volume control in dB */
#define SDL_VOLUME_STEP (0.75)

 /* no AV sync correction is done if below the minimum AV sync threshold */
#define AV_SYNC_THRESHOLD_MIN 0.04
 /* AV sync correction is done if above the maximum AV sync threshold */
#define AV_SYNC_THRESHOLD_MAX 0.1
 /* If a frame duration is longer than this, it will not be duplicated to compensate AV sync */
#define AV_SYNC_FRAMEDUP_THRESHOLD 0.1
 /* no AV correction is done if too big error */
#define AV_NOSYNC_THRESHOLD 10.0

 /* maximum audio speed change to get correct sync */
#define SAMPLE_CORRECTION_PERCENT_MAX 10

 /* external clock speed adjustment constants for realtime sources based on buffer fullness */
#define EXTERNAL_CLOCK_SPEED_MIN  0.900
#define EXTERNAL_CLOCK_SPEED_MAX  1.010
#define EXTERNAL_CLOCK_SPEED_STEP 0.001

 /* we use about AUDIO_DIFF_AVG_NB A-V differences to make the average */
#define AUDIO_DIFF_AVG_NB   20

 /* polls for possible required screen refresh at least this often, should be less than 1/fps */
#define REFRESH_RATE 0.01

 /* NOTE: the size must be big enough to compensate the hardware audio buffersize size */
 /* TODO: We assume that a decoded and resampled frame fits into this buffer */
#define SAMPLE_ARRAY_SIZE (8 * 65536)

#define CURSOR_HIDE_DELAY 1000000

#define USE_ONEPASS_SUBTITLE_RENDER 1









//单例模式
class VideoCtl : public QObject
{
    Q_OBJECT

public:
    //explicit VideoCtl(QObject *parent = nullptr);

    static VideoCtl* GetInstance();

	/**
	* @brief	开始播放
	*
	* @param	strFileName 文件完整路径
	* @param	widPlayWid 播放窗口id
	* @return	true 成功 false 失败
	* @note
	*/
	bool StartPlay(QString strFileName, WId widPlayWid);

signals:
    void SigPlayMsg(QString strMsg);//< 错误信息
    void SigFrameDimensionsChanged(int nFrameWidth, int nFrameHeight); //<视频宽高发生变化

private slots:

private:
    explicit VideoCtl(QObject *parent = nullptr);
	/**
	 * @brief	初始化
	 * 
	 * @return	true 成功 false 失败
	 * @note 	
	 */
    bool Init();

	/**
	 * @brief	连接信号槽
	 * 
	 * @return	true 成功 false 失败
	 * @note 	
	 */
    bool ConnectSignalSlots();

public:


private:

    static VideoCtl* m_pInstance; //< 单例指针

    bool m_bInited;	//< 初始化标志

};

#endif // VIDEOCTL_H
