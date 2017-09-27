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
    //鼠标按下事件
    void mousePressEvent(QMouseEvent *event);
   //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event);
   //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);
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

    //计算点的区域
    void region(const QPoint &cursorGlobalPoint);
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

    CtrlBar     *m_pCtrlBar;    //播放控制面板
    Playlist    *m_pPlaylist;   //播放列表面板
    Title       *m_pTitle;      //标题栏面板
    DisplayWid     *m_pDisplay;    //显示区域

    QPoint  move_point;     //移动的距离
    bool    m_bLeftMousePress;    //鼠标按下
    QPoint dragPosition;// 窗口移动拖动时需要记住的点
    Direction dir;        // 窗口大小改变时，记录改变方向
};

#endif // MainWid_H
