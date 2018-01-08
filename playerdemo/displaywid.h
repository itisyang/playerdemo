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
class DisplayWid;
}

class DisplayWid : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayWid(QWidget *parent = 0);
    ~DisplayWid();

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
private slots:
	/**
	 * @brief	接收一帧图像
	 * 
	 * @param	img 一帧图像
	 * @note 	
	 */
    void OnImage(QPixmap& img);
	/**
	 * @brief	显示信息
	 * 
	 * @param	strMsg 信息内容
	 * @note 	
	 */
	void OnDisplayMsg(QString strMsg);
signals:
    void SigAddFile(QString strFileName);///< 增加视频文件
	void SigAddFile(QString strFileName, WId widPlayWid);
private:
    Ui::DisplayWid *ui;

    VideoCtl *m_VideoCtl;	//< 视频控制
};

#endif // DISPLAY_H
