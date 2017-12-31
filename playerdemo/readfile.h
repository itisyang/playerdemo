/**
 * @file
 * @brief   读取文件线程
 * @author  itisyang
 * @date    20171221
 * @note
 */

#ifndef READFILE_H
#define READFILE_H

#include <QObject>
#include "customthread.h"
#include "globalhelper.h"

class ReadFile : public CustomThread
{
    Q_OBJECT
public:
    explicit ReadFile();

    /**
     * @brief   线程入口
     * @param
     * @return
     * @note
     */
    void run();
    /**
     * @brief  开始读取
     * @param
     * @return 错误码
     * @note
     */
    int  StartRead(QString strFilePath);
signals:
    void SigPlayMsg(QString strMsg);    ///< 播放信息信号

    void SigStartVideoDec();            ///< 视频解码信号
    void SigStartAudioDec();            ///< 音频解码信号
    void SigStartSubtitleDec();         ///< 字幕解码信号

public slots:
    /**
     * @brief   开始读取文件
     * @param   strFilePath 文件名
     * @return  错误码
     * @note
     */
    int OnStartRead(QString strFilePath);
private:
    QString m_strFilePath;          ///< 文件名
    AVFormatContext *m_pFormatCtx;  ///< 视频文件格式上下文
};

#endif // READFILE_H
