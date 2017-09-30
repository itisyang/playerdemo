#include <QFile>
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QAbstractItemView>
#include <QMimeData>
#include <QSizeGrip>

#include "MainWid.h"
#include "ui_MainWid.h"

#include "globalhelper.h"


const int gShadowWidth = 3;//边框阴影宽度

MainWid::MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWid)
{
    ui->setupUi(this);
    //无边框、无系统菜单、 任务栏点击最小化
    setWindowFlags(Qt::FramelessWindowHint /*| Qt::WindowSystemMenuHint*/ | Qt::WindowMinimizeButtonHint);
    // 追踪鼠标
    this->setMouseTracking(true);

    //保证窗口不被绘制上的部分透明
    setAttribute(Qt::WA_TranslucentBackground);

    //加载样式
    setStyleSheet(GlobalHelper::GetQssStr(":/qss/MainWid.css"));


    m_pCtrlBar = new CtrlBar(this);
    m_pPlaylist = new Playlist(this);
    m_pTitle = new Title(this);

//    m_pCtrlBar->hide();
//    m_pPlaylist->hide();
//    m_pTitle->hide();


    m_bLeftMousePress = false;

    //setMouseTracking(true);

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
    m_bLeftMousePress = false;
    dir = NONE;
}

MainWid::~MainWid()
{
    delete ui;
}

void MainWid::paintEvent(QPaintEvent *event)
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


void MainWid::mousePressEvent(QMouseEvent *event)
{
    switch(event->button())
    {
        case Qt::LeftButton:
            m_bLeftMousePress = true;
            if(dir != NONE)
            {
                this->mouseGrabber();
            }
            else
            {
                //鼠标相对于窗体的位置（或者使用event->globalPos() - this->pos()）
                //dragPosition = event->globalPos() - this->frameGeometry().topLeft();
                move_point = event->pos();
            }
            break;
        case Qt::RightButton:

        default:
            QWidget::mousePressEvent(event);

    }
}

void MainWid::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(event->button() == Qt::LeftButton)
    {
        //设置鼠标为未被按下
        m_bLeftMousePress = false;

        if(dir != NONE)
        {
            this->releaseMouse();
            this->setCursor(QCursor(Qt::ArrowCursor));
        }
    }

}

void MainWid::mouseMoveEvent(QMouseEvent *event)
{
    QPoint gloPoint = event->globalPos();
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    this->region(gloPoint);

    qDebug() << "MainWid::mouseMoveEvent";
    //若鼠标左键被按下
    if (!m_bLeftMousePress)
    {

    }
    else
    {
        if (isMaximized())
        {
            showNormal();
            m_bLeftMousePress = !m_bLeftMousePress;//避免窗体移动
        }
        else
        {
            if(dir != NONE)
            {
                QRect rMove(tl, rb);

                switch(dir) {
                case LEFT:
                    if(rb.x() - gloPoint.x() <= this->minimumWidth())
                        rMove.setX(tl.x());
                    else
                        rMove.setX(gloPoint.x());
                    break;
                case RIGHT:
                    rMove.setWidth(gloPoint.x() - tl.x());
                    break;
                case UP:
                    if(rb.y() - gloPoint.y() <= this->minimumHeight())
                        rMove.setY(tl.y());
                    else
                        rMove.setY(gloPoint.y());
                    break;
                case DOWN:
                    rMove.setHeight(gloPoint.y() - tl.y());
                    break;
                case LEFTTOP:
                    if(rb.x() - gloPoint.x() <= this->minimumWidth())
                        rMove.setX(tl.x());
                    else
                        rMove.setX(gloPoint.x());
                    if(rb.y() - gloPoint.y() <= this->minimumHeight())
                        rMove.setY(tl.y());
                    else
                        rMove.setY(gloPoint.y());
                    break;
                case RIGHTTOP:
                    rMove.setWidth(gloPoint.x() - tl.x());
                    rMove.setY(gloPoint.y());
                    break;
                case LEFTBOTTOM:
                    rMove.setX(gloPoint.x());
                    rMove.setHeight(gloPoint.y() - tl.y());
                    break;
                case RIGHTBOTTOM:
                    rMove.setWidth(gloPoint.x() - tl.x());
                    rMove.setHeight(gloPoint.y() - tl.y());
                    break;
                default:
                    break;
                }
                this->setGeometry(rMove);
            }
            else
            {
                //鼠标相对于屏幕的位置
                QPoint move_pos = event->globalPos();

                //移动主窗体位置
                this->move(move_pos - move_point);
                //qDebug() << "MainWid::mouseMoveEvent";
                event->accept();
            }

        }

    }
    QWidget::mouseMoveEvent(event);
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

    if (1)
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

    m_pCtrlBar->move(0 + gShadowWidth, height() - 80 - gShadowWidth);
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


void MainWid::region(const QPoint &cursorGlobalPoint)
{
    qDebug() << "MainWid::region";
    // 获取窗体在屏幕上的位置区域，tl为topleft点，rb为rightbottom点
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    int x = cursorGlobalPoint.x();
    int y = cursorGlobalPoint.y();

    if(tl.x() + gShadowWidth >= x && tl.x() <= x && tl.y() + gShadowWidth >= y && tl.y() <= y)
    {
    // 左上角
        dir = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
    } else if(x >= rb.x() - gShadowWidth && x <= rb.x() && y >= rb.y() - gShadowWidth && y <= rb.y())
    {
        // 右下角
        dir = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if(x <= tl.x() + gShadowWidth && x >= tl.x() && y >= rb.y() - gShadowWidth && y <= rb.y())
    {
        //左下角
        dir = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= rb.x() && x >= rb.x() - gShadowWidth && y >= tl.y() && y <= tl.y() + gShadowWidth)
    {
        // 右上角
        dir = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= tl.x() + gShadowWidth && x >= tl.x())
    {
        // 左边
        dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    } else if( x <= rb.x() && x >= rb.x() - gShadowWidth)
    {
        // 右边
        dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }else if(y >= tl.y() && y <= tl.y() + gShadowWidth)
    {
        // 上边
        dir = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    } else if(y <= rb.y() && y >= rb.y() - gShadowWidth)
    {
        // 下边
        dir = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }else
    {
        // 默认
        dir = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}
