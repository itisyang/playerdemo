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
#include <QPixmap>
#include <QString>

#include "globalhelper.h"


#include "readfile.h"
#include "videodec.h"
#include "audiodec.h"
#include "subtitledec.h"
#include "videodataoprator.h"
#include <playthread.h>

//单例模式
class VideoCtl : public QObject
{
    Q_OBJECT

public:
    //explicit VideoCtl(QObject *parent = nullptr);

    static VideoCtl* GetInstance();
    static void ReleaseInstance();
	/**
	 * @brief	开始播放
	 * 
	 * @param	strFileName 文件完整路径
	 * @return	true 成功 false 失败
	 * @note 	
	 */
    bool StartPlay(QString strFileName);
	/**
	* @brief	开始播放
	*
	* @param	strFileName 文件完整路径
	* @param	widPlayWid 播放窗口id
	* @return	true 成功 false 失败
	* @note
	*/
	bool StartPlay(QString strFileName, WId widPlayWid);

    AVFormatContext* GetAVFormatCtx();

    VideoDataOprator* GetVideoDataOprator();

	/**
	 * @brief	打开流
	 * 
	 * @param	nVideoStreamIndex 视频流序号
	 * @param	nAudioStreamIndex 音频流序号
	 * @param	nSubtitleStreamIndex 字幕流序号
	 * @return	true 成功 false 失败
	 * @note 	
	 */
    bool StreamComponentOpen(int nVideoStreamIndex, int nAudioStreamIndex, int nSubtitleStreamIndex);

signals:
    void SigStartDec();				//< 开始解码信号
	void SigStartPlay(WId wid);			//< 开始播放显示信号
    void SigPlayMsg(QString strMsg);//< 错误信息
    void SigImage(QPixmap& img);	//< 一帧图像
public slots:
    void OnPlayMsg(QString strMsg); //< 播放消息
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

    static VideoCtl* m_pInstance;

    bool m_bInited;	//< 初始化标志

    ReadFile m_ReadFile;//< 文件读取

    VideoDataOprator m_VideoDataOprator;//< 数据处理

    VideoDec m_VideoDec;		//< 视频解码
    AudioDec m_AudioDec;		//< 音频解码
    SubtitleDec m_SubtitleDec;	//< 字幕解码

	PlayThread m_PlayThread;	//< 播放线程

    static const QString strProgrameBirthYear;//< 程序初始创建年

    AVFormatContext *m_pAVFormatContext; //< FFmpeg视频文件格式解析结构体
};

#endif // VIDEOCTL_H
