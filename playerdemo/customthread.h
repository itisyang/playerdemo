/**
 * @file
 * @brief   自定义线程抽象类
 * @author  itisyang
 * @date    20171221
 * @note
 */

#ifndef CUSTOMTHREAD_H
#define CUSTOMTHREAD_H

#include <QThread>

class CustomThread : public QThread
{
public:
    CustomThread();
    ~CustomThread();

    /**
     * @brief   线程运行入口（纯虚函数）
     * @param
     * @return
     * @note
     */
    virtual void run() = 0;

    /**
     * @brief  启动线程
     * @param
     * @return  true 成功 false 失败
     * @note
     */
    bool StartThread();

    /**
     * @brief  停止线程
     * @param
     * @return  true 成功 false 失败
     * @note
     */
    bool StopThread();

protected:
    bool m_bRunning;    ///< 线程运行标志位
};

#endif // CUSTOMTHREAD_H
