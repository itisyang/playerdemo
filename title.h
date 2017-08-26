#ifndef MAINWIDTITLE_H
#define MAINWIDTITLE_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class Title;
}

class Title : public QWidget
{
    Q_OBJECT

public:
    explicit Title(QWidget *parent = 0);
    ~Title();
private:
    void paintEvent(QPaintEvent *event);
    //双击
    void mouseDoubleClickEvent(QMouseEvent *event);
signals:
    void SigCloseBtnClicked();
    void SigMinBtnClicked();
    void SigMaxBtnClicked();
    void SigDoubleClicked();
private:
    Ui::Title *ui;

};

#endif // MAINWIDTITLE_H
