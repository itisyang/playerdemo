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
}
