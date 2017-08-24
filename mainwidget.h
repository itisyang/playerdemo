#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMouseEvent>


namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
private:
    //鼠标按下事件
    void mousePressEvent(QMouseEvent *event);
   //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event);
   //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);
private:
    Ui::MainWidget *ui;

    QPoint move_point; //移动的距离
    bool mouse_press; //鼠标按下
};

#endif // MAINWIDGET_H
