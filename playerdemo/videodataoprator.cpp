#include "videodataoprator.h"

VideoDataOprator::VideoDataOprator(QObject *parent) : QObject(parent),
  m_nMaxNumFrameCache(10)
{

}
//存放原始数据
bool VideoDataOprator::PutData(AVPacket *pkt, DATA_TYPE type)
{
    switch (type) {
    case VIDEO_DATA:
		if (PutDataVideo(pkt) == false)
		{
			return false;
		}
        break;
    case AUDIO_DATA:
        if (PutDataAudio(pkt) == false)
		{
			return false;
		}
        break;
    case SUBTITLE_DATA:
        if (PutDataSubtitle(pkt) == false)
		{
			return false;
		}
        break;
    default:
        break;
    }

    return true;
}
//获取原始数据
bool VideoDataOprator::GetData(AVPacket& pkt, DATA_TYPE type)
{
	bool bRet = false;
    switch (type) {
    case VIDEO_DATA:
		bRet = GetDataVideo(pkt);
        break;
    case AUDIO_DATA:
        //GetDataAudio(pkt);
        break;
    case SUBTITLE_DATA:
        //GetDataSubtitle(pkt);
        break;
    default:
        break;
    }

    return bRet;
}
//存放解码数据
bool VideoDataOprator::PutDataDec(AVFrame *frame, DATA_TYPE type)
{
    switch (type) {
    case VIDEO_DATA:
        PutDataDecVideo(frame);
        break;
    case AUDIO_DATA:
        PutDataDecAudio(frame);
        break;
    case SUBTITLE_DATA:
        PutDataDecSubtitle(frame);
        break;
    default:
        break;
    }

    return true;
}
//获取解码数据
bool VideoDataOprator::GetDataDec(AVFrame *frame, DATA_TYPE type)
{
    switch (type) {
    case VIDEO_DATA:
        GetDataDecVideo(frame);
        break;
    case AUDIO_DATA:
        GetDataDecAudio(frame);
        break;
    case SUBTITLE_DATA:
        GetDataDecSubtitle(frame);
        break;
    default:
        break;
    }

    return true;
}

bool VideoDataOprator::PutDataVideo(AVPacket *pkt)
{
    while(1)
    {
        if (m_mutexV.tryLock())
        {
            if (m_listV.size() < m_nMaxNumFrameCache)
            {
				AVPacket avpkt;
				memcpy(&avpkt, pkt, sizeof(AVPacket));
                m_listV.append(avpkt);
                m_mutexV.unlock();
                break;
            }
            else
            {
                m_mutexV.unlock();
				return false;
            }
        }
        else
        {
			return false;
        }
    }


    return true;
}

bool VideoDataOprator::GetDataVideo(AVPacket& pkt)
{
    if (m_mutexV.tryLock())
    {
        if (m_listV.size() > 0)
        {
			pkt = m_listV.takeFirst();
            m_mutexV.unlock();
            return true;
        }
        else
        {
            m_mutexV.unlock();
            return false;
        }
    }

    return false;
}

bool VideoDataOprator::PutDataDecVideo(AVFrame *frame)
{
    if (m_mutexVDec.tryLock())
    {
        if (m_ListVDec.size() < m_nMaxNumFrameCache)
        {
            m_ListVDec.append(*frame);
        }

        m_mutexVDec.unlock();
    }

    return true;
}

bool VideoDataOprator::GetDataDecVideo(AVFrame *frame)
{
    if (m_mutexVDec.tryLock())
    {
        if (m_ListVDec.size() > 0)
        {
            *frame = m_ListVDec.takeFirst();
        }

        m_mutexVDec.unlock();
    }

    return true;
}

bool VideoDataOprator::PutDataAudio(AVPacket *pkt)
{
    if (m_mutexA.tryLock())
    {
        if (m_listA.size() < m_nMaxNumFrameCache)
        {
            m_listA.append(*pkt);
        }

        m_mutexA.unlock();
    }

    return true;
}

bool VideoDataOprator::GetDataAudio(AVPacket *pkt)
{
    if (m_mutexA.tryLock())
    {
        if (m_listA.size() > 0)
        {
            *pkt = m_listA.takeFirst();
        }

        m_mutexA.unlock();
    }

    return true;
}

bool VideoDataOprator::PutDataDecAudio(AVFrame *frame)
{
    if (m_mutexADec.tryLock())
    {
        if (m_ListADec.size() < m_nMaxNumFrameCache)
        {
            m_ListADec.append(*frame);
        }

        m_mutexADec.unlock();
    }

    return true;
}

bool VideoDataOprator::GetDataDecAudio(AVFrame *frame)
{
    if (m_mutexADec.tryLock())
    {
        if (m_ListADec.size() > 0)
        {
            *frame = m_ListADec.takeFirst();
        }

        m_mutexADec.unlock();
    }

    return true;
}

bool VideoDataOprator::PutDataSubtitle(AVPacket *pkt)
{
    if (m_mutexS.tryLock())
    {
        if (m_listS.size() < m_nMaxNumFrameCache)
        {
            m_listS.append(*pkt);
        }

        m_mutexS.unlock();
    }

    return true;
}

bool VideoDataOprator::GetDataSubtitle(AVPacket *pkt)
{
    if (m_mutexS.tryLock())
    {
        if (m_listS.size() > 0)
        {
            *pkt = m_listS.takeFirst();
        }

        m_mutexS.unlock();
    }

    return true;
}

bool VideoDataOprator::PutDataDecSubtitle(AVFrame *frame)
{
    if (m_mutexSDec.tryLock())
    {
        if (m_ListSDec.size() < m_nMaxNumFrameCache)
        {
            m_ListSDec.append(*frame);
        }

        m_mutexSDec.unlock();
    }

    return true;
}

bool VideoDataOprator::GetDataDecSubtitle(AVFrame *frame)
{
    if (m_mutexSDec.tryLock())
    {
        if (m_ListSDec.size() > 0)
        {
            *frame = m_ListSDec.takeFirst();
        }

        m_mutexSDec.unlock();
    }

    return true;
}
