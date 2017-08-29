#include <QFile>
#include <QPainter>
#include <QtMath>

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

    //保证窗口不被绘制上的部分透明
    setAttribute(Qt::WA_TranslucentBackground);

    //加载样式
    setStyleSheet(GlobalHelper::GetQssStr(":/qss/mainwidget.qss"));

    //连接自定义信号与槽
    ConnectSignalSlots();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (!this->isMaximized() && !this->isFullScreen())
    {//边框阴影
//        int nShadowWidth = 3;
//        this->layout()->setMargin(nShadowWidth);

//        QPainterPath path;
//        path.setFillRule(Qt::WindingFill);
//        path.addRect(nShadowWidth, nShadowWidth,
//                     this->width() - nShadowWidth*2, this->height() - nShadowWidth*2);

//        QPainter painter(this);
//        painter.setRenderHint(QPainter::Antialiasing, true);
//        painter.fillPath(path, QBrush(Qt::white));

//        QColor color(0, 0, 0, 50);
//        for(int i = 0; i < nShadowWidth; i++)
//        {
//            QPainterPath path;
//            path.setFillRule(Qt::WindingFill);
//            //path.addRoundRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2, 1, 1);
//            path.addRect(nShadowWidth - i,
//                         nShadowWidth - i,
//                         this->width() - (nShadowWidth - i ) * 2,
//                         this->height() - (nShadowWidth - i) * 2);
//            color.setAlpha(150 - qSqrt(i) * 50);
//            painter.setPen(color);
//            painter.drawPath(path);
//        }
    }
    else
    {
        int nShadowWidth = 0;
        this->layout()->setMargin(nShadowWidth);
    }
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
    connect(this, SIGNAL(SigShowMax(bool)), ui->TitleWid, SLOT(OnChangeMaxBtnStyle(bool)));
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
        emit SigShowMax(false);
    }
    else
    {
        showMaximized();
        emit SigShowMax(true);
    }
}

void MainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    //设置鼠标为未被按下
    mouse_press = false;
}
