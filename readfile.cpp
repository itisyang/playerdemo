#include "readfile.h"

ReadFile::ReadFile(QObject *parent) : QObject(parent)
{

}

int ReadFile::OnStartRead(QString strFileName)
{

    return NoError;
}
