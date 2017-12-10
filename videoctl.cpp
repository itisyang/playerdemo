#include "VideoCtl.h"
#include <QThread>
#include <QDebug>

const QString VideoCtl::strProgrameBirthYear = "2017";

VideoCtl::VideoCtl(QObject *parent) : QObject(parent)
{
    m_bInited = false;

#if CONFIG_AVDEVICE
    //注册所有设备
    avdevice_register_all();
#endif
#if CONFIG_AVFILTER
    //注册所有过滤器
    avfilter_register_all();
#endif
    //注册所有复用器、编码器
    av_register_all();
    //网络格式初始化
    avformat_network_init();


}

bool VideoCtl::Init()
{
    if (m_bInited == true)
    {
        return true;
    }

    if (ConnectSignalSlots() == false)
    {
        return false;
    }

    m_bInited = true;
}

bool VideoCtl::ConnectSignalSlots()
{
    QList<bool> listRet;
    bool bRet;
    bRet = connect(this, SIGNAL(SigStartDec()), &m_VideoDec, SLOT(OnStartDec()));
    listRet.append(bRet);


    foreach (bRet, listRet)
    {
        if (bRet == false)
        {
            return false;
        }
    }
}

VideoCtl *VideoCtl::m_pInstance = new VideoCtl();

VideoCtl *VideoCtl::GetInstance()
{
    return m_pInstance;
}

VideoCtl *VideoCtl::ReleaseInstance()
{

}

bool VideoCtl::StartPlay(QString FileName)
{
    qDebug() << "VideoCtl Thread ID:" << QThread::currentThreadId();
    emit SigStartDec();
}

