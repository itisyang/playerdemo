#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMouseEvent>

#include "ctrlbar.h"
#include "playlist.h"
#include "title.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
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
private:


    //连接信号槽
    void ConnectSignalSlots();

    //调整模块显示位置
    void AdjustUiPos();
private slots:
    void OnCloseBtnClicked();
    void OnMinBtnClicked();
    void OnMaxBtnClicked();
signals:
    void SigShowMax(bool bIfMax);
private:
    Ui::MainWidget *ui;

    CtrlBar     *m_pCtrlBar;    //播放控制面板
    Playlist    *m_pPlaylist;   //播放列表面板
    Title       *m_pTitle;      //标题栏面板

    QPoint  move_point;     //移动的距离
    bool    m_bMousePress;    //鼠标按下
};

#endif // MAINWIDGET_H
