#ifndef MainWid_H
#define MainWid_H

#include <QWidget>
#include <QMouseEvent>
#include <QDragEnterEvent>

#include "ctrlbar.h"
#include "playlist.h"
#include "title.h"
#include "displaywid.h"

enum Direction { UP=0, DOWN=1, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };


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

    //调整模块显示位置
    void AdjustUiPos();
private slots:
    //关闭、最小化、最大化按钮响应
    void OnCloseBtnClicked();
    void OnMinBtnClicked();
    void OnMaxBtnClicked();
signals:
    //最大化信号
    void SigShowMax(bool bIfMax);
private:
    Ui::MainWid *ui;

    bool m_bPlaying;//正在播放

    CtrlBar     *m_pCtrlBar;    //播放控制面板
    Playlist    *m_pPlaylist;   //播放列表面板
    Title       *m_pTitle;      //标题栏面板
    DisplayWid  *m_pDisplay;    //显示区域
};

#endif // MainWid_H
