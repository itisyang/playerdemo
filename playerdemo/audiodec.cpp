#include <QDebug>

#include "audiodec.h"

AudioDec::AudioDec()
{

}

void AudioDec::run()
{
    while (m_bRunning)
    {
        qDebug() << "AudioDec Thread ID:" << QThread::currentThreadId();
        break;
    }
}

int AudioDec::OnStartDec()
{
    StartThread();

    return NoError;
}
