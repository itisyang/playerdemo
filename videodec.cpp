#include <QDebug>
#include "videodec.h"
#include "videoctl.h"

VideoDec::VideoDec()
{

}

void VideoDec::run()
{

    while (m_bRunning)
    {


        qDebug() << "VideoDec Thread ID:" << QThread::currentThreadId();
        break;
    }
}

void VideoDec::OnStartDec()
{
    StartThread();
}
