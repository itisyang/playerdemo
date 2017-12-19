#include "subtitledec.h"

SubtitleDec::SubtitleDec()
{

}

void SubtitleDec::run()
{
    while (m_bRunning)
    {

    }
}

int SubtitleDec::OnStartDec()
{
    StartThread();

    return NoError;
}
