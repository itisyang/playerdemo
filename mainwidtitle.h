#ifndef MAINWIDTITLE_H
#define MAINWIDTITLE_H

#include <QWidget>

namespace Ui {
class MainWidTitle;
}

class MainWidTitle : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidTitle(QWidget *parent = 0);
    ~MainWidTitle();

private:
    Ui::MainWidTitle *ui;
};

#endif // MAINWIDTITLE_H
