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
#include <QMenu>
#include <QAction>
#include <QPropertyAnimation>
#include <QTimer>
#include <QMainWindow>

#include "playlist.h"
#include "title.h"
#include "settingwid.h"

namespace Ui {
class MainWid;
}

class MainWid : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWid(QMainWindow *parent = 0);
    ~MainWid();

    //初始化
    bool Init();
protected:
    //绘制
    void paintEvent(QPaintEvent *event);

//     //窗口大小变化事件
//     void resizeEvent(QResizeEvent *event);
//     //窗口移动事件
//     void moveEvent(QMoveEvent *event);

    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    //void dragEnterEvent(QDragEnterEvent *event);
    //void dragMoveEvent(QDragMoveEvent *event);
    //void dropEvent(QDropEvent *event);

    //按键事件
    void keyReleaseEvent(QKeyEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void contextMenuEvent(QContextMenuEvent* event);


private:
    //连接信号槽
    bool ConnectSignalSlots();

    //关闭、最小化、最大化按钮响应
    void OnCloseBtnClicked();
    void OnMinBtnClicked();
    void OnMaxBtnClicked();
    //显示、隐藏播放列表
    void OnShowOrHidePlaylist();



    /**
    * @brief	全屏播放
    */
    void OnFullScreenPlay();

    void OnCtrlBarAnimationTimeOut();
    void OnFullscreenMouseDetectTimeOut();

    void OnCtrlBarHideTimeOut();
    void OnShowMenu();
    void OnShowAbout();
    void OpenFile();

    void OnShowSettingWid();

signals:
    //最大化信号
    void SigShowMax(bool bIfMax);
    void SigSeekForward();
    void SigSeekBack();
    void SigAddVolume();
    void SigSubVolume();
    void SigPlayOrPause();
    void SigOpenFile(QString strFilename);
private:
    Ui::MainWid *ui;

    bool m_bPlaying; ///< 正在播放

//     CtrlBar     *m_pCtrlBar;    ///< 播放控制面板
//     Playlist    *m_pPlaylist;   ///< 播放列表面板
//     Title       *m_pTitle;      ///< 标题栏面板
//     DisplayWid  *m_pDisplay;    ///< 显示区域
//     PlaylistCtrlBar *m_pPlaylistCtrlBar; ///< 播放列表控制按钮

    const int m_nShadowWidth; ///< 阴影宽度

    bool m_bFullScreenPlay; ///< 全屏播放标志

    QPropertyAnimation *m_stCtrlbarAnimationShow; //全屏时控制面板浮动显示
    QPropertyAnimation *m_stCtrlbarAnimationHide; //全屏时控制面板浮动显示
    QRect m_stCtrlBarAnimationShow;//控制面板显示区域
    QRect m_stCtrlBarAnimationHide;//控制面板隐藏区域

    QTimer m_stCtrlBarAnimationTimer;
    QTimer m_stFullscreenMouseDetectTimer;//全屏时鼠标位置监测时钟
    bool m_bFullscreenCtrlBarShow;
    QTimer stCtrlBarHideTimer;

    Playlist m_stPlaylist;
    Title m_stTitle;

    bool m_bMoveDrag;//移动窗口标志
    QPoint m_DragPosition;

    About m_stAboutWidget;
    SettingWid m_stSettingWid;

    QMenu m_stMenu;
    QAction m_stActExit;
    QAction m_stActAbout;
    QAction m_stActOpen;
    QAction m_stActFullscreen;
};

#endif // MainWid_H
