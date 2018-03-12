#include "videodataoprator.h"

VideoDataOprator::VideoDataOprator(QObject *parent) : QObject(parent),
  m_nMaxNumFrameCache(60)
{

}

bool VideoDataOprator::Init()
{
	for (int i = 0; i < m_nMaxNumFrameCache; i++)
	{

	}

	return true;
}
#if 0
bool VideoDataOprator::PutAVPacketData(AVPacket *pkt, DATA_TYPE type)
{
    bool bRet = true;

    switch (type) {
    case VIDEO_DATA:
        if (m_listAVPacketV.size() < m_nMaxNumFrameCache)
        {
            m_mutexAVPacketV.lock();

            AVPacket *pAVPacket = new AVPacket;
            memcpy(pAVPacket, pkt, sizeof(AVPacket));
            m_listAVPacketV.append(pAVPacket);

            m_condAVPacketV.wakeOne();

            m_mutexAVPacketV.unlock();
        }
        else
        {
            bRet = false;
        }
        break;
    case AUDIO_DATA:

        break;
    case SUBTITLE_DATA:

        break;
    default:
        break;
    }

    return bRet;
}

bool VideoDataOprator::GetAVPacketData(AVPacket& pkt, DATA_TYPE type)
{
	bool bRet = true;
    switch (type) {
    case VIDEO_DATA:
        //获取视频数据帧
    {
        m_mutexAVPacketV.lock();
        if (m_listAVPacketV.size() <= 0)
        {
            m_condAVPacketV.wait(&m_mutexAVPacketV);
        }

        AVPacket* pAVPacket = m_listAVPacketV.takeFirst();
        m_mutexAVPacketV.unlock();

        memcpy(&pkt, pAVPacket, sizeof(AVPacket));
        delete pAVPacket;
        pAVPacket = nullptr;
    }

        break;
    case AUDIO_DATA:
        
        break;
    case SUBTITLE_DATA:
        
        break;
    default:
        break;
    }

    return bRet;
}
//存放解码数据
bool VideoDataOprator::PutAVFrameData(Frame* frame, DATA_TYPE type)
{
    bool bRet = true;
    switch (type) {
    case VIDEO_DATA:
    {
        if (m_ListAVFrameV.size() < m_nMaxNumFrameCache)
        {
            m_mutexAVFrameV.lock();

            Frame *pFrame = new Frame;
            memcpy(pFrame, frame, sizeof(Frame));
            m_ListAVFrameV.append(pFrame);

            m_condAVFrameV.wakeOne();

            m_mutexAVFrameV.unlock();

        }
        else
        {
            bRet = false;
        }
    }

    break;

    case AUDIO_DATA:

        break;
    case SUBTITLE_DATA:

        break;
    default:
        break;
    }

    return bRet;
}

//获取解码数据
bool VideoDataOprator::GetAVFrameData(Frame &frame, DATA_TYPE type)
{
	bool bRet = true;
    switch (type) {
    case VIDEO_DATA:
    {
        //取出解码后的视频帧
        m_mutexAVFrameV.lock();
        if (m_ListAVFrameV.size() <= 0)
        {
            m_condAVFrameV.wait(&m_mutexAVFrameV);
        }

        Frame* pFrame = m_ListAVFrameV.takeFirst();
        m_mutexAVFrameV.unlock();

        memcpy(&frame, pFrame, sizeof(Frame));
        delete pFrame;
        pFrame = nullptr;
    }

    break;
    
    case AUDIO_DATA:
		
		break;
    case SUBTITLE_DATA:
		
		break;
    default:
		return false;
    }

	return bRet;
}
#endif