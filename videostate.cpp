#include "videostate.h"

const QString VideoState::strProgrameBirthYear = "2017";

VideoState::VideoState(QObject *parent) : QObject(parent)
{

}

VideoState *VideoState::m_pInstance = new VideoState();

VideoState *VideoState::GetInstance()
{
    return m_pInstance;
}

