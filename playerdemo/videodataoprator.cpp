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
bool VideoDataOprator::PutAVFrameData(AVFrame *frame, DATA_TYPE type)
{
	bool bRet = true;
    switch (type) {
    case VIDEO_DATA:
    {
        if (m_ListAVFrameV.size() < m_nMaxNumFrameCache)
        {
            m_mutexAVFrameV.lock();

            AVFrame *pAVFrame = new AVFrame;
            memcpy(pAVFrame, frame, sizeof(AVFrame));
            m_ListAVFrameV.append(pAVFrame);

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
bool VideoDataOprator::GetAVFrameData(AVFrame &frame, DATA_TYPE type)
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

        AVFrame* pAVFrame = m_ListAVFrameV.takeFirst();
        m_mutexAVFrameV.unlock();

        memcpy(&frame, pAVFrame, sizeof(AVFrame));
        delete pAVFrame;
        pAVFrame = nullptr;
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
