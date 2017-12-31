#include <QDebug>
#include "subtitledec.h"

SubtitleDec::SubtitleDec()
{

}

void SubtitleDec::run()
{
    while (m_bRunning)
    {
        qDebug() << "SubtitleDec Thread ID:" << QThread::currentThreadId();
        break;
    }
}

int SubtitleDec::OnStartDec()
{
    StartThread();

    return NoError;
}
