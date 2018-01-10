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
	 * #param	wid 画面显示窗口句柄
	 * @brief	开始播放
	 */
	void OnStarPlay(WId wid);
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
private:
// 	SDL_Window *window;
// 	SDL_Renderer *renderer;

	SDL_Texture *vid_texture; //<

	WId m_WId; //< 画面显示窗口句柄


	SwsContext *img_convert_ctx;
};

