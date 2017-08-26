#ifndef MAINWIDTITLE_H
#define MAINWIDTITLE_H

#include <QWidget>

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
private:
    Ui::Title *ui;

};

#endif // MAINWIDTITLE_H
