/*
 * @file 	audiodec.h
 * @date 	2018/01/07 11:11
 *
 * @author 	itisyang
 * @Contact	itisyang@gmail.com
 *
 * @brief 	音频解码线程
 * @note
 */


#ifndef AUDIODEC_H
#define AUDIODEC_H

#include <QObject>

#include "globalhelper.h"
#include "customthread.h"

class AudioDec : public CustomThread
{
    Q_OBJECT
public:
    explicit AudioDec();


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

private:

	/**
	* @brief   线程入口
	*/
	void run();
};

#endif // AUDIODEC_H
