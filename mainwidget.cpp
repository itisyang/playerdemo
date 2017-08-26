#include <QFile>

#include "mainwidget.h"
#include "ui_mainwidget.h"

#include "globalhelper.h"


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    //无边框、无系统菜单、 任务栏点击最小化
    setWindowFlags(Qt::FramelessWindowHint /*| Qt::WindowSystemMenuHint*/ | Qt::WindowMinimizeButtonHint);

    setStyleSheet(GlobalHelper::GetQssStr(":/qss/mainwidget.qss"));

    ConnectSignalSlots();
}

MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && ui->TitleWid->height() >= event->pos().y())
    {
        mouse_press = true;
        //鼠标相对于窗体的位置（或者使用event->globalPos() - this->pos()）
        move_point = event->pos();
    }
}
void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    //若鼠标左键被按下
    if(mouse_press)
    {
        //鼠标相对于屏幕的位置
        QPoint move_pos = event->globalPos();

        //移动主窗体位置
        this->move(move_pos - move_point);
    }
}

void MainWidget::ConnectSignalSlots()
{
    connect(ui->TitleWid, SIGNAL(SigCloseBtnClicked()), this, SLOT(OnCloseBtnClicked()));
    connect(ui->TitleWid, SIGNAL(SigMaxBtnClicked()), this, SLOT(OnMaxBtnClicked()));
    connect(ui->TitleWid, SIGNAL(SigMinBtnClicked()), this, SLOT(OnMinBtnClicked()));
    connect(ui->TitleWid, SIGNAL(SigDoubleClicked()), this, SLOT(OnMaxBtnClicked()));
}

void MainWidget::OnCloseBtnClicked()
{
    this->close();
}

void MainWidget::OnMinBtnClicked()
{
    this->showMinimized();
}

void MainWidget::OnMaxBtnClicked()
{
    if (isMaximized())
    {
        showNormal();
    }
    else
    {
        showMaximized();
    }
}

void MainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    //设置鼠标为未被按下
    mouse_press = false;
}
