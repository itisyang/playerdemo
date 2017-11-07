#include "audiodec.h"

AudioDec::AudioDec(QObject *parent) : QObject(parent)
{

}

int AudioDec::OnStartDec()
{
    return ERROR_NO_ERROR;
}
