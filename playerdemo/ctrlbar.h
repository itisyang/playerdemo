/*
 * @file 	ctrlbar.h
 * @date 	2018/01/07 10:46
 *
 * @author 	itisyang
 * @Contact	itisyang@gmail.com
 *
 * @brief 	控制面板界面
 * @note
 */
#ifndef CTRLBAR_H
#define CTRLBAR_H

#include <QWidget>

namespace Ui {
class CtrlBar;
}

class CtrlBar : public QWidget
{
    Q_OBJECT

public:
    explicit CtrlBar(QWidget *parent = 0);
    ~CtrlBar();
	/**
	 * @brief	初始化UI
	 * 
	 * @return	true 成功 false 失败
	 * @note 	
	 */
    bool InitUi();
    /**
     * @brief	连接信号槽
     * 
     * @param	
     * @return	
     * @note 	
     */
    bool ConnectSignalSlots();
public slots:
    void OnVideoTotalSeconds(int nSeconds);
    void OnVideoPlaySeconds(int nSeconds);

signals:
    void SigShowOrHidePlaylist();	//< 显示或隐藏信号
private:
    Ui::CtrlBar *ui;
};

#endif // CTRLBAR_H
