/**
 * @file
 * @brief   音频解码线程
 * @author  itisyang
 * @date    20171221
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
    /**
     * @brief   线程入口
     * @param
     * @return
     * @note
     */
    void run();

signals:

public slots:

    /**
     * @brief   开始解码
     * @param
     * @return  错误码
     * @note
     */
    int OnStartDec();
};

#endif // AUDIODEC_H
