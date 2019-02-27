#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

namespace Ui { class About; };

class About : public QWidget
{
    Q_OBJECT

public:
    About(QWidget *parent = Q_NULLPTR);
    ~About();
    bool Init();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
 private slots:
    void on_ClosePushButton_clicked();
private:
    Ui::About *ui;

    bool m_bMoveDrag;//移动窗口标志
    QPoint m_DragPosition;
};
