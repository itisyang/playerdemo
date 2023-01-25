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
    bool Init();

public:
    void OnVideoTotalSeconds(int nSeconds);
    void OnVideoPlaySeconds(int nSeconds);
    void OnVideopVolume(double dPercent);
    void OnPauseStat(bool bPaused);
    void OnStopFinished();
private:
    void OnPlaySliderValueChanged();
    void OnVolumeSliderValueChanged();
private slots:
    void on_PlayOrPauseBtn_clicked();
    void on_VolumeBtn_clicked();
    void on_StopBtn_clicked();
    void on_SettingBtn_clicked();

    /**
    * @brief	连接信号槽
    *
    * @param
    * @return
    * @note
    */
    bool ConnectSignalSlots();
signals:
    void SigShowOrHidePlaylist();	//< 显示或隐藏信号
    void SigPlaySeek(double dPercent); ///< 调整播放进度
    void SigPlayVolume(double dPercent);
    void SigPlayOrPause();
    void SigStop();
    void SigForwardPlay();
    void SigBackwardPlay();
    void SigShowMenu();
    void SigShowSetting();
private:
    Ui::CtrlBar *ui;

    int m_nTotalPlaySeconds;
    double m_dLastVolumePercent;
};

#endif // CTRLBAR_H
