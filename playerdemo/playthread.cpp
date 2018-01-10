#include <QDebug>

#include "playthread.h"

PlayThread::PlayThread()
{
}


PlayThread::~PlayThread()
{
}

void PlayThread::OnStarPlay()
{
	StartThread();
}

void PlayThread::run()
{
	qDebug() << "PlayThread::run";
	//SDL_UpdateYUVTexture
	//SDL_UpdateTexture
	//SDL_RenderCopyEx
	//SDL_RenderCopy

	AVFrame avframe;
	

}
