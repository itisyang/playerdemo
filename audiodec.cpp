#include "audiodec.h"

AudioDec::AudioDec()
{

}

void AudioDec::run()
{
    while (m_bRunning)
    {

    }
}

int AudioDec::OnStartDec()
{
    StartThread();

    return NoError;
}
