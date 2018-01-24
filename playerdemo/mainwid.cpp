#include <QFile>
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QAbstractItemView>
#include <QMimeData>
#include <QSizeGrip>
#include <QWindow>

#include "mainwid.h"
#include "ui_mainwid.h"
#include "framelesshelper.h"
#include "globalhelper.h"

MainWid::MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWid),
    m_nShadowWidth(0)
{
    ui->setupUi(this);
    //无边框、无系统菜单、 任务栏点击最小化
    setWindowFlags(Qt::FramelessWindowHint /*| Qt::WindowSystemMenuHint*/ | Qt::WindowMinimizeButtonHint);
    //加载样式
    QString qss = GlobalHelper::GetQssStr(":/Resources/qss/mainwid.css");
    //qDebug() << qss;
    setStyleSheet(qss);


//     m_pTitle = new Title(this);
//     m_pDisplay = new Show(this);
//     m_pPlaylist = new Playlist(this);
//     m_pCtrlBar = new CtrlBar(this);
//     m_pPlaylistCtrlBar = new PlaylistCtrlBar(this);

    FramelessHelper *pHelper = new FramelessHelper(this);
    pHelper->activateOn(this);  //激活当前窗体
    pHelper->setTitleHeight(ui->TitleWid->height());  //设置窗体的标题栏高度
    pHelper->setWidgetMovable(true);  //设置窗体可移动
    pHelper->setWidgetResizable(true);  //设置窗体可缩放
    pHelper->setRubberBandOnMove(true);  //设置橡皮筋效果-可移动
    pHelper->setRubberBandOnResize(true);  //设置橡皮筋效果-可缩放

    // 追踪鼠标
    //this->setMouseTracking(true);

    //保证窗口不被绘制上的部分透明
    //setAttribute(Qt::WA_TranslucentBackground);




    //连接自定义信号与槽
    ConnectSignalSlots();

    //接受放下事件
    //setAcceptDrops(true);
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

    m_bFullScreenPlay = false;

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
        int nShadowWidth = m_nShadowWidth;
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

    OnAdjustUi();
}

void MainWid::moveEvent(QMoveEvent *event)
{
    Q_UNUSED(event);

    OnAdjustUi();
}

void MainWid::enterEvent(QEvent *event)
{
    Q_UNUSED(event);

//    m_pCtrlBar->show();
//    m_pPlaylist->show();
//    m_pTitle->show();
}

void MainWid::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);

//    if (m_bPlaying)
//    {
//        m_pCtrlBar->hide();
//        m_pPlaylist->hide();
//        m_pTitle->hide();
//    }
}

bool MainWid::ConnectSignalSlots()
{
	QList<bool> listRet;
	bool bRet;

	bRet = connect(ui->TitleWid, SIGNAL(SigCloseBtnClicked()), this, SLOT(OnCloseBtnClicked()));
	listRet.append(bRet);
	bRet = connect(ui->TitleWid, SIGNAL(SigMaxBtnClicked()), this, SLOT(OnMaxBtnClicked()));
	listRet.append(bRet);
	bRet = connect(ui->TitleWid, SIGNAL(SigMinBtnClicked()), this, SLOT(OnMinBtnClicked()));
	listRet.append(bRet);
	bRet = connect(ui->TitleWid, SIGNAL(SigDoubleClicked()), this, SLOT(OnMaxBtnClicked()));
	listRet.append(bRet);
	bRet = connect(this, SIGNAL(SigShowMax(bool)), ui->TitleWid, SLOT(OnChangeMaxBtnStyle(bool)));
	listRet.append(bRet);
	bRet = connect(ui->PlaylistWid, SIGNAL(SigUpdateUi()), this, SLOT(OnAdjustUi()));
	listRet.append(bRet);
	bRet = connect(ui->PlaylistWid, SIGNAL(SigPlay(QString)), ui->ShowWid, SIGNAL(SigPlay(QString)));
	listRet.append(bRet);
	

	bRet = connect(ui->ShowWid, SIGNAL(SigAddFile(QString)), ui->PlaylistWid, SLOT(OnAddFile(QString)));
	listRet.append(bRet);

    bRet = connect(ui->ShowWid, SIGNAL(SigFullScreen()), this, SLOT(OnFullScreenPlay()));
    listRet.append(bRet);

	bRet = connect(ui->CtrlBarWid, SIGNAL(SigShowOrHidePlaylist()), this, SLOT(OnShowOrHidePlaylist()));
	listRet.append(bRet);
    

	for (bool bReturn : listRet)
	{
		if (bReturn == false)
		{
			return false;
		}
	}

	return true;
}


void MainWid::keyPressEvent(QKeyEvent *event)
{
// 	    // 是否按下Ctrl键      特殊按键
//     if(event->modifiers() == Qt::ControlModifier){
//         // 是否按下M键    普通按键  类似
//         if(event->key() == Qt::Key_M)
//             ···
//     }

	switch (event->key())
	{
	case Qt::Key_F://全屏

        OnFullScreenPlay();
		break;
	default:
		break;
	}
}

void MainWid::OnAdjustUi()
{
#if 0
    //标题栏位置
    m_pTitle->move(m_nShadowWidth, m_nShadowWidth);
    m_pTitle->setFixedWidth(width() - m_nShadowWidth * 2);

    //显示区域位置
    m_pDisplay->move(m_nShadowWidth, m_nShadowWidth + m_pTitle->height());
    int nDisplayW = 0;
    int nDisplayH = 0;
    nDisplayH = this->height() - m_pTitle->height() - m_pCtrlBar->height() - m_nShadowWidth*2;
    if (m_pPlaylist->GetPlaylistStatus())//播放列表显示
    {
        nDisplayW = this->width() - m_pPlaylist->width() - m_nShadowWidth*2;
    }
    else
    {
        nDisplayW = this->width() - m_nShadowWidth*2;
    }

    m_pDisplay->setFixedSize(nDisplayW, nDisplayH);

    //播放列表位置
    int nPlaylistWidth = m_pPlaylist->width();
    m_pPlaylist->move(width() - nPlaylistWidth - m_nShadowWidth, m_pTitle->height() + m_nShadowWidth);
    m_pPlaylist->setFixedHeight(height() - m_pTitle->height() - m_pCtrlBar->height() - m_nShadowWidth * 2);

    if (m_pPlaylist->GetPlaylistStatus())//播放列表显示
    {
        m_pPlaylistCtrlBar->move(width() - nPlaylistWidth - m_nShadowWidth - m_pPlaylistCtrlBar->width(),
                                 m_pTitle->height() + m_nShadowWidth + nDisplayH/2);

    }
    else
    {
        m_pPlaylistCtrlBar->move(width() - m_nShadowWidth - m_pPlaylistCtrlBar->width(),
                                 m_pTitle->height() + m_nShadowWidth + nDisplayH / 2);
    }

    m_pPlaylistCtrlBar->setFixedHeight(70);


    //播放控制面板位置
    m_pCtrlBar->move(m_nShadowWidth, height() - 80 - m_nShadowWidth);
    m_pCtrlBar->setFixedSize(width() - m_nShadowWidth * 2, 80);
#endif
}

void MainWid::OnFullScreenPlay()
{
    qDebug() << "MainWid::OnFullScreenPlay()";
    if (m_bFullScreenPlay == false)
    {
        m_bFullScreenPlay = true;
        ui->ShowWid->setWindowFlags(Qt::Window);
        //多屏情况下，在当前屏幕全屏
        ui->ShowWid->windowHandle()->setScreen(qApp->screens().last());
        ui->ShowWid->showFullScreen();
    }
    else
    {
        m_bFullScreenPlay = false;
        ui->ShowWid->setWindowFlags(Qt::SubWindow);
        ui->ShowWid->showFullScreen();
    }
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

void MainWid::OnShowOrHidePlaylist()
{
     if (ui->PlaylistWid->isHidden())
     {
         ui->PlaylistWid->show();
     }
     else
     {
         ui->PlaylistWid->hide();
     }

     //OnAdjustUi();
}

