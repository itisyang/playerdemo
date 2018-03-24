/*
 * @file 	displaywid.h
 * @date 	2018/01/07 11:11
 *
 * @author 	itisyang
 * @Contact	itisyang@gmail.com
 *
 * @brief 	显示控件
 * @note
 */
#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>

#include "videoctl.h"

namespace Ui {
class Show;
}

class Show : public QWidget
{
    Q_OBJECT

public:
    Show(QWidget *parent);
    ~Show();
	/**
	 * @brief	初始化
	 */
	bool Init();

protected:
	/**
	 * @brief	拖拽释放事件
	 * 
	 * @param	event 事件指针
	 * @note 	
	 */
    void dropEvent(QDropEvent *event);
	/**
	 * @brief	拖拽事件
	 *
	 * @param	event 事件指针
	 * @note
	 */
    void dragEnterEvent(QDragEnterEvent *event);
    /**
     * @brief	窗口大小变化事件
     * 
     * @param	event 事件指针
     * @note
     */
    void resizeEvent(QResizeEvent *event);

    /**
     * @brief	按键事件
     * 
     * @param	
     * @return	
     * @note 	
     */
    void keyPressEvent(QKeyEvent *event);
private slots:
	/**
	 * @brief	显示信息
	 * 
	 * @param	strMsg 信息内容
	 * @note 	
	 */
	void OnDisplayMsg(QString strMsg);
	/**
	* @brief	播放
	*
	* @param	strFile 文件名
	* @note
	*/
	void OnPlay(QString strFile);
    /**
     * @brief	视频宽高发生变化
     * 
     * @param	nFrameWidth 宽
     * @param	nFrameHeight 高
     * @return	
     * @note 	
     */
    void OnFrameDimensionsChanged(int nFrameWidth, int nFrameHeight);
private:
	/**
	 * @brief	连接信号槽	
	 */
	bool ConnectSignalSlots();
    /**
    * @brief	调整显示画面的宽高，使画面保持原比例
    *
    * @param	nFrameWidth 视频宽
    * @param	nFrameWHeight 视频高
    * @return
    * @note
    */
    void AdjustDisplay(int nFrameWidth, int nFrameHeight);
signals:
    void SigAddFile(QString strFileName);///< 增加视频文件
	void SigPlay(QString strFile); ///<播放
								   
	void SigFullScreen();//全屏播放
private:
    Ui::Show *ui;

    int m_nLastFrameWidth; ///< 记录视频宽高
    int m_nLastFrameHeight;
};

#endif // DISPLAY_H
