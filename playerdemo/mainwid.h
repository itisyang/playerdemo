/*
 * @file 	mainwid.h
 * @date 	2018/01/07 11:12
 *
 * @author 	itisyang
 * @Contact	itisyang@gmail.com
 *
 * @brief 	主界面
 * @note
 */
#ifndef MainWid_H
#define MainWid_H

#include <QWidget>
#include <QMouseEvent>
#include <QDragEnterEvent>

#include "ctrlbar.h"
#include "playlist.h"
#include "title.h"
#include "displaywid.h"
#include "playlistctrlbar.h"


namespace Ui {
class MainWid;
}

class MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit MainWid(QWidget *parent = 0);
    ~MainWid();
protected:
    //绘制
    void paintEvent(QPaintEvent *event);

    //窗口大小变化事件
    void resizeEvent(QResizeEvent *event);
    //窗口移动事件
    void moveEvent(QMoveEvent *event);

    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    //void dragEnterEvent(QDragEnterEvent *event);
    //void dragMoveEvent(QDragMoveEvent *event);
    //void dropEvent(QDropEvent *event);
private:

    //连接信号槽
    void ConnectSignalSlots();

private slots:
    //关闭、最小化、最大化按钮响应
    void OnCloseBtnClicked();
    void OnMinBtnClicked();
    void OnMaxBtnClicked();
    //显示、隐藏播放列表
    void OnShowOrHidePlaylist();

    //调整窗口模块
    void OnAdjustUi();
signals:
    //最大化信号
    void SigShowMax(bool bIfMax);
private:
    Ui::MainWid *ui;

    bool m_bPlaying; ///< 正在播放

    CtrlBar     *m_pCtrlBar;    ///< 播放控制面板
    Playlist    *m_pPlaylist;   ///< 播放列表面板
    Title       *m_pTitle;      ///< 标题栏面板
    DisplayWid  *m_pDisplay;    ///< 显示区域
    PlaylistCtrlBar *m_pPlaylistCtrlBar; ///< 播放列表控制按钮

    const int m_nShadowWidth; ///< 阴影宽度
};

#endif // MainWid_H
