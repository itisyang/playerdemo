#include "customthread.h"

CustomThread::CustomThread()
{

}

CustomThread::~CustomThread()
{

}

bool CustomThread::StartThread()
{
    m_bRunning = true;
    if (!this->isRunning())
    {
        this->start();
    }
}

bool CustomThread::StopThread()
{
    m_bRunning = false;
}
