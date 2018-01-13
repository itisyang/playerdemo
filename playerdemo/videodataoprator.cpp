#include "videodataoprator.h"

VideoDataOprator::VideoDataOprator(QObject *parent) : QObject(parent),
  m_nMaxNumFrameCache(10)
{

}

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
	bool bRet = false;
    switch (type) {
    case VIDEO_DATA:
		bRet = PutDataDecVideo(frame);
		break;
    case AUDIO_DATA:
		bRet = PutDataDecAudio(frame);
		break;
    case SUBTITLE_DATA:
		bRet = PutDataDecSubtitle(frame);
        break;
    default:
        break;
    }

    return bRet;
}
//获取解码数据
bool VideoDataOprator::GetDataDec(AVFrame &frame, DATA_TYPE type)
{
	bool bRet = false;
    switch (type) {
    case VIDEO_DATA:
		bRet = GetDataDecVideo(frame);
		break;
    case AUDIO_DATA:
		bRet = GetDataDecAudio(frame);
		break;
    case SUBTITLE_DATA:
		bRet = GetDataDecSubtitle(frame);
		break;
    default:
		return false;
    }

	return bRet;
}

bool VideoDataOprator::PutDataVideo(AVPacket *pkt)
{
	if (m_listV.size() < m_nMaxNumFrameCache)
	{
		if (m_mutexV.tryLock())
		{
			AVPacket *pAVPacket = new AVPacket;
			memcpy(pAVPacket, pkt, sizeof(AVPacket));
			m_listV.append(pAVPacket);
			m_mutexV.unlock();
		}
		else
		{
			return false;
		}

	}
	else
	{
		return false;
	}

    return true;
}

bool VideoDataOprator::GetDataVideo(AVPacket& pkt)
{
    if (m_listV.size() > 0)
    {
		if (m_mutexV.tryLock())
		{
			AVPacket* pAVPacket = m_listV.takeFirst();
			m_mutexV.unlock();

			memcpy(&pkt, pAVPacket, sizeof(AVPacket));
			delete pAVPacket;
			pAVPacket = NULL;
		}
		else
		{
			return false;
		}
    }
    else
    {
        return false;
    }

	return true;
}

bool VideoDataOprator::PutDataDecVideo(AVFrame *frame)
{
	if (m_ListVDec.size() < m_nMaxNumFrameCache)
	{
		if (m_mutexVDec.tryLock())
		{
			AVFrame *pAVFrame = new AVFrame;
			memcpy(pAVFrame, frame, sizeof(AVFrame));
			m_ListVDec.append(pAVFrame);
			m_mutexVDec.unlock();
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

    return true;
}

bool VideoDataOprator::GetDataDecVideo(AVFrame& frame)
{
	if (m_listV.size() > 0)
	{
		if (m_mutexVDec.tryLock())
		{
			AVFrame* pAVFrame = m_ListVDec.takeFirst();
			m_mutexVDec.unlock();

			memcpy(&frame, pAVFrame, sizeof(AVFrame));
			delete pAVFrame;
			pAVFrame = NULL;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
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

bool VideoDataOprator::GetDataDecAudio(AVFrame &frame)
{
    if (m_mutexADec.tryLock())
    {
        if (m_ListADec.size() > 0)
        {
            frame = m_ListADec.takeFirst();
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

bool VideoDataOprator::GetDataDecSubtitle(AVFrame& frame)
{
    if (m_mutexSDec.tryLock())
    {
        if (m_ListSDec.size() > 0)
        {
            frame = m_ListSDec.takeFirst();
        }

        m_mutexSDec.unlock();
    }

    return true;
}
