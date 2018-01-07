/*
 * @file 	subtitledec.h
 * @date 	2018/01/07 11:11
 *
 * @author 	itisyang
 * @Contact	itisyang@gmail.com
 *
 * @brief 	字幕解码线程
 * @note
 */

#ifndef SUBTITLEDEC_H
#define SUBTITLEDEC_H

#include <QObject>
#include "globalhelper.h"
#include "customthread.h"
class SubtitleDec : public CustomThread
{
    Q_OBJECT
public:
    explicit SubtitleDec();
    /**
     * @brief   线程入口
     */
    void run();

signals:
    void SigPlayMsg(QString strMsg);    ///< 播放信息信号
public slots:
    /**
     * @brief   开始解码
     *
     * @return  错误码
     * @note
     */
    int OnStartDec();
};

#endif // SUBTITLEDEC_H
