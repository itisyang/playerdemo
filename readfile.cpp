#include "readfile.h"
#include <QDebug>
ReadFile::ReadFile()
{

}

void ReadFile::run()
{
    if (m_strFilePath.isEmpty())
    {
        return;
    }
    while (m_bRunning)
    {

        break;
    }
}

int ReadFile::OnStartRead(QString strFilePath)
{
    m_strFilePath = strFilePath;

    StartThread();

    return NoError;
}
