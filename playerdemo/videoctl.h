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
#include "datactl.h"



//单例模式
class VideoCtl : public QObject
{
    Q_OBJECT

public:
    //explicit VideoCtl(QObject *parent = nullptr);

    static VideoCtl* GetInstance();
    ~VideoCtl();
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

    void SigVideoTotalSeconds(int nSeconds);
    void SigVideoPlaySeconds(int nSeconds);

    void SigVideoVolume(double dPercent);
    void SigPauseStat(bool bPaused);

    void SigStop();
public slots:
    void OnPlaySeek(double dPercent);
    void OnPlayVolume(double dPercent);
    void OnSeekForward();
    void OnSeekBack();
    void OnAddVolume();
    void OnSubVolume();
    void OnPause();
    void OnStop();
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

    void ReadThread(VideoState *CurStream);
    void LoopThread(VideoState *CurStream);
    VideoState *stream_open(const char *filename);

    void refresh_loop_wait_event(VideoState *is, SDL_Event *event);
    void video_refresh(void *opaque, double *remaining_time);
    //更新音量
    void UpdateVolume(int sign, double step);

    void video_display(VideoState *is);
    int video_open(VideoState *is);
    void do_exit(VideoState *is);
public:


private:

    static VideoCtl* m_pInstance; //< 单例指针

    bool m_bInited;	//< 初始化标志
    bool m_bPlayLoop; //刷新循环标志

    VideoState* m_CurStream;

    SDL_Window *window;

    WId play_wid;//播放窗口


    /* options specified by the user */
    int screen_width;
    int screen_height;

};

#endif // VIDEOCTL_H
