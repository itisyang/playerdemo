#include <QFile>
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include "mainwidget.h"
#include "ui_mainwidget.h"

#include "globalhelper.h"


const int gShadowWidth = 3;//边框阴影宽度

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


    m_pCtrlBar = new CtrlBar(this);
    m_pPlaylist = new Playlist(this);
    m_pTitle = new Title(this);


    m_bMousePress = false;

    //setMouseTracking(true);

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
        int nShadowWidth = gShadowWidth;
        this->layout()->setMargin(nShadowWidth);

        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(nShadowWidth, nShadowWidth,
                     this->width() - nShadowWidth*2, this->height() - nShadowWidth*2);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.fillPath(path, QBrush(Qt::white));

        QColor color(0, 0, 0, 50);
        for(int i = 0; i < nShadowWidth; i++)
        {
            QPainterPath path;
            path.setFillRule(Qt::WindingFill);
            //path.addRoundRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2, 1, 1);
            path.addRect(nShadowWidth - i,
                         nShadowWidth - i,
                         this->width() - (nShadowWidth - i ) * 2,
                         this->height() - (nShadowWidth - i) * 2);
            color.setAlpha(150 - qSqrt(i) * 50);
            painter.setPen(color);
            painter.drawPath(path);
        }
    }
    else
    {
        int nShadowWidth = 0;
        this->layout()->setMargin(nShadowWidth);
    }
}


void MainWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && m_pTitle->height() >= event->pos().y())
    {
        m_bMousePress = true;
        //鼠标相对于窗体的位置（或者使用event->globalPos() - this->pos()）
        move_point = event->pos();
    }
}
void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    //若鼠标左键被按下
    if(m_bMousePress)
    {
        //鼠标相对于屏幕的位置
        QPoint move_pos = event->globalPos();

        //移动主窗体位置
        this->move(move_pos - move_point);
        //qDebug() << "MainWidget::mouseMoveEvent";
    }
}

void MainWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    AdjustUiPos();
}

void MainWidget::moveEvent(QMoveEvent *event)
{
    Q_UNUSED(event);

    AdjustUiPos();

}

void MainWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event);

    //QRect rectCtrl = QRect(m_pCtrlBar->pos(), m_pCtrlBar->size());
//    QPoint pointCtrl = this->pos() + m_pCtrlBar->pos();
//    QRect rectCtrl = QRect(pointCtrl.x(), pointCtrl.y(), width(), 100);
//    QPoint pos = cursor().pos();
//    qDebug() << pos;
//    if (rectCtrl.contains(pos))
//    {
//        m_pCtrlBar->show();
//    }
//    else
//    {
//        m_pCtrlBar->hide();
//    }

    m_pCtrlBar->show();
    m_pPlaylist->show();
    m_pTitle->show();
}

void MainWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);

//    QRect rectCtrl = QRect(m_pCtrlBar->pos(), m_pCtrlBar->size());
//    if (rectCtrl.contains(cursor().pos()))
//    {
//        m_pCtrlBar->show();
//    }
//    else
//    {
//        m_pCtrlBar->hide();
//    }
    if (0)
    {
        m_pCtrlBar->hide();
        m_pPlaylist->hide();
        m_pTitle->hide();
    }

}

void MainWidget::ConnectSignalSlots()
{
    connect(m_pTitle, SIGNAL(SigCloseBtnClicked()), this, SLOT(OnCloseBtnClicked()));
    connect(m_pTitle, SIGNAL(SigMaxBtnClicked()), this, SLOT(OnMaxBtnClicked()));
    connect(m_pTitle, SIGNAL(SigMinBtnClicked()), this, SLOT(OnMinBtnClicked()));
    connect(m_pTitle, SIGNAL(SigDoubleClicked()), this, SLOT(OnMaxBtnClicked()));
    connect(this, SIGNAL(SigShowMax(bool)), m_pTitle, SLOT(OnChangeMaxBtnStyle(bool)));
}

void MainWidget::AdjustUiPos()
{
    m_pTitle->move(gShadowWidth, gShadowWidth);
    m_pTitle->setFixedWidth(width() - gShadowWidth * 2);

    m_pCtrlBar->move(0 + gShadowWidth, height() - 80 - gShadowWidth);
    m_pCtrlBar->setFixedSize(width() - gShadowWidth * 2, 80);

    int nPlaylistWidth = m_pPlaylist->width();
    m_pPlaylist->move(width() - nPlaylistWidth - gShadowWidth, m_pTitle->height() + gShadowWidth);
    m_pPlaylist->setFixedHeight(height() - m_pTitle->height() - m_pCtrlBar->height() - gShadowWidth * 2);
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
    m_bMousePress = false;
}
