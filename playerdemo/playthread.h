/*
 * @file 	playthread.h
 * @date 	2018/01/09 7:21
 *
 * @author 	itisyang
 * @Contact	itisyang@gmail.com
 *
 * @brief 	播放渲染线程
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
private slots:

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
	int realloc_texture(SDL_Texture **texture, Uint32 new_format, int new_width, int new_height, SDL_BlendMode blendmode, int init_texture);
	int upload_texture(SDL_Texture *tex, AVFrame *frame, struct SwsContext **img_convert_ctx);
signals:
	void SigFrameDimensionsChanged(int nFrameWidth, int nFrameHeight); //<视频宽高发生变化
private:
	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Texture *vid_texture; //<

	WId m_WId; //< 画面显示窗口句柄


	SwsContext *img_convert_ctx;


	bool m_bIsFullScreen;//< 是否全屏
};

