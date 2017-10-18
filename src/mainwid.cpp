#include <QFile>
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QAbstractItemView>
#include <QMimeData>
#include <QSizeGrip>

#include "MainWid.h"
#include "ui_MainWid.h"
#include "framelesshelper.h"
#include "globalhelper.h"


const int gShadowWidth = 2;//边框阴影宽度

MainWid::MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWid)
{
    ui->setupUi(this);
    //无边框、无系统菜单、 任务栏点击最小化
    setWindowFlags(Qt::FramelessWindowHint /*| Qt::WindowSystemMenuHint*/ | Qt::WindowMinimizeButtonHint);

    m_pCtrlBar = new CtrlBar(this);
    m_pPlaylist = new Playlist(this);
    m_pTitle = new Title(this);
    m_pDisplay = new DisplayWid(this);

    FramelessHelper *pHelper = new FramelessHelper(this);
    pHelper->activateOn(this);  //激活当前窗体
    pHelper->setTitleHeight(m_pTitle->height());  //设置窗体的标题栏高度
    pHelper->setWidgetMovable(true);  //设置窗体可移动
    pHelper->setWidgetResizable(true);  //设置窗体可缩放
    pHelper->setRubberBandOnMove(true);  //设置橡皮筋效果-可移动
    pHelper->setRubberBandOnResize(true);  //设置橡皮筋效果-可缩放

    // 追踪鼠标
    //this->setMouseTracking(true);

    //保证窗口不被绘制上的部分透明
    //setAttribute(Qt::WA_TranslucentBackground);

    //加载样式
    setStyleSheet(GlobalHelper::GetQssStr(":/qss/MainWid.css"));


    //连接自定义信号与槽
    ConnectSignalSlots();

    //接受放下事件
    setAcceptDrops(true);
    //可以清晰地看到放下过程中的图标指示
    //setDropIndicatorShown(true);

//    setAcceptDrops(true);
//    setDragDropMode(QAbstractItemView::DragDrop);
//    setDragEnabled(true);
//    setDropIndicatorShown(true);

    //窗口大小调节
//    QSizeGrip   *pSizeGrip = new QSizeGrip(this);
//    pSizeGrip->setMinimumSize(10, 10);
//    pSizeGrip->setMaximumSize(10, 10);
//    ui->verticalLayout->addWidget(pSizeGrip, 0, Qt::AlignBottom | Qt::AlignRight);

    m_bPlaying = false;
}

MainWid::~MainWid()
{
    delete ui;
}

void MainWid::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
#if 0
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

#endif
}


void MainWid::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    AdjustUiPos();
}

void MainWid::moveEvent(QMoveEvent *event)
{
    Q_UNUSED(event);

    AdjustUiPos();

}

void MainWid::enterEvent(QEvent *event)
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

void MainWid::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);

    if (m_bPlaying)
    {
        m_pCtrlBar->hide();
        m_pPlaylist->hide();
        m_pTitle->hide();
    }
}

void MainWid::ConnectSignalSlots()
{
    connect(m_pTitle, SIGNAL(SigCloseBtnClicked()), this, SLOT(OnCloseBtnClicked()));
    connect(m_pTitle, SIGNAL(SigMaxBtnClicked()), this, SLOT(OnMaxBtnClicked()));
    connect(m_pTitle, SIGNAL(SigMinBtnClicked()), this, SLOT(OnMinBtnClicked()));
    connect(m_pTitle, SIGNAL(SigDoubleClicked()), this, SLOT(OnMaxBtnClicked()));
    connect(this, SIGNAL(SigShowMax(bool)), m_pTitle, SLOT(OnChangeMaxBtnStyle(bool)));
}

void MainWid::AdjustUiPos()
{
    m_pTitle->move(gShadowWidth, gShadowWidth);
    m_pTitle->setFixedWidth(width() - gShadowWidth * 2);

    m_pDisplay->move(gShadowWidth, gShadowWidth + m_pTitle->height());
    m_pDisplay->setFixedSize(this->width() - m_pPlaylist->width() - gShadowWidth*2,
                             this->height() - m_pTitle->height() - m_pCtrlBar->height() - gShadowWidth*2);

    m_pCtrlBar->move(gShadowWidth, height() - 80 - gShadowWidth);
    m_pCtrlBar->setFixedSize(width() - gShadowWidth * 2, 80);

    int nPlaylistWidth = m_pPlaylist->width();
    m_pPlaylist->move(width() - nPlaylistWidth - gShadowWidth, m_pTitle->height() + gShadowWidth);
    m_pPlaylist->setFixedHeight(height() - m_pTitle->height() - m_pCtrlBar->height() - gShadowWidth * 2);

}

void MainWid::OnCloseBtnClicked()
{
    this->close();
}

void MainWid::OnMinBtnClicked()
{
    this->showMinimized();
}

void MainWid::OnMaxBtnClicked()
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

