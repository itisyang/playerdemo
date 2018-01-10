/*
 * @file 	playthread.h
 * @date 	2018/01/09 7:21
 *
 * @author 	itisyang
 * @Contact	itisyang@gmail.com
 *
 * @brief 	控制播放进度
 * @note
 */

#pragma once
#include "customthread.h"
#include "globalhelper.h"
class PlayThread :
	public CustomThread
{
	Q_OBJECT
public:
	PlayThread();
	~PlayThread();
public slots:
	/**
	 * @brief	开始播放
	 */
	void OnStarPlay();
private:
	/**
	* @brief	线程入口
	*/
	void run();

	/**
	 * @brief	
	 * 
	 * @param	
	 * @return	
	 * @note 	
	 */

};

