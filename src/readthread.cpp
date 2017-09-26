#include "readthread.h"

ReadThread::ReadThread()
{

}

ReadThread::~ReadThread()
{

}

bool ReadThread::StartThread(QString strVideoName)
{
    m_strVideoName = strVideoName;
    m_bThreadRunning = true;

    this->start();

    return true;
}

bool ReadThread::StopThread()
{
    m_bThreadRunning = false;

    return true;
}

void ReadThread::run()
{
    while(m_bThreadRunning)
    {

    }
}
