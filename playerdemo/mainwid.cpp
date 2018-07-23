/*
 * @file 	mainwid.cpp
 * @date 	2018/03/10 22:26
 *
 * @author 	itisyang
 * @Contact	itisyang@gmail.com
 *
 * @brief 	主窗口
 * @note
 */
#include <QFile>
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QAbstractItemView>
#include <QMimeData>
#include <QSizeGrip>
#include <QWindow>
#include <QDesktopWidget>
#include <QScreen>

#include "mainwid.h"
#include "ui_mainwid.h"
#include "framelesshelper.h"
#include "globalhelper.h"
#include "videoctl.h"

MainWid::MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWid),
    m_nShadowWidth(0),
    m_stActionGroup(this),
    m_stMenu(this)
{
    ui->setupUi(this);
    //无边框、无系统菜单、 任务栏点击最小化
    setWindowFlags(Qt::FramelessWindowHint /*| Qt::WindowSystemMenuHint*/ | Qt::WindowMinimizeButtonHint);
    //设置任务栏图标
    this->setWindowIcon(QIcon(":/Resources/player.png"));
    //加载样式
    QString qss = GlobalHelper::GetQssStr(":/Resources/qss/mainwid.css");
    setStyleSheet(qss);

    // 追踪鼠标 用于播放时隐藏鼠标
    this->setMouseTracking(true);

    ui->ShowWid->setMouseTracking(true);

    //保证窗口不被绘制上的部分透明
    //setAttribute(Qt::WA_TranslucentBackground);

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

bool MainWid::Init()
{

    FramelessHelper *pHelper = new FramelessHelper(this); //无边框管理
    pHelper->activateOn(this);  //激活当前窗体
    pHelper->setTitleHeight(ui->TitleWid->height());  //设置窗体的标题栏高度
    pHelper->setWidgetMovable(true);  //设置窗体可移动
    pHelper->setWidgetResizable(true);  //设置窗体可缩放
    pHelper->setRubberBandOnMove(true);  //设置橡皮筋效果-可移动
    pHelper->setRubberBandOnResize(true);  //设置橡皮筋效果-可缩放

    //连接自定义信号与槽
    if (ConnectSignalSlots() == false)
    {
        return false;
    }

    if (ui->CtrlBarWid->Init() == false || 
        ui->PlaylistWid->Init() == false || 
        ui->ShowWid->Init() == false || 
        ui->TitleWid->Init() == false)
    {
        return false;
    }


    m_stCtrlbarAnimation = new QPropertyAnimation(ui->CtrlBarWid, "pos");

    return true;
}

void MainWid::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}


void MainWid::enterEvent(QEvent *event)
{
    Q_UNUSED(event);

}

void MainWid::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);

}

bool MainWid::ConnectSignalSlots()
{
	connect(ui->TitleWid, &Title::SigCloseBtnClicked, this, &MainWid::OnCloseBtnClicked);
	connect(ui->TitleWid, &Title::SigMaxBtnClicked, this, &MainWid::OnMaxBtnClicked);
	connect(ui->TitleWid, &Title::SigMinBtnClicked, this, &MainWid::OnMinBtnClicked);
	connect(ui->TitleWid, &Title::SigDoubleClicked, this, &MainWid::OnMaxBtnClicked);
    connect(ui->TitleWid, &Title::SigFullScreenBtnClicked, this, &MainWid::OnFullScreenPlay);
    connect(ui->TitleWid, &Title::SigOpenFile, ui->PlaylistWid, &Playlist::OnAddFileAndPlay);

    connect(ui->PlaylistWid, &Playlist::SigPlay, ui->ShowWid, &Show::SigPlay);

	connect(ui->ShowWid, &Show::SigOpenFile, ui->PlaylistWid, &Playlist::OnAddFileAndPlay);
    connect(ui->ShowWid, &Show::SigFullScreen, this, &MainWid::OnFullScreenPlay);
    connect(ui->ShowWid, &Show::SigPlayOrPause, VideoCtl::GetInstance(), &VideoCtl::OnPause);
    connect(ui->ShowWid, &Show::SigStop, VideoCtl::GetInstance(), &VideoCtl::OnStop);

    connect(ui->CtrlBarWid, &CtrlBar::SigShowOrHidePlaylist, this, &MainWid::OnShowOrHidePlaylist);
    connect(ui->CtrlBarWid, &CtrlBar::SigPlaySeek, VideoCtl::GetInstance(), &VideoCtl::OnPlaySeek);
    connect(ui->CtrlBarWid, &CtrlBar::SigPlayVolume, VideoCtl::GetInstance(), &VideoCtl::OnPlayVolume);
    connect(ui->CtrlBarWid, &CtrlBar::SigPlayOrPause, VideoCtl::GetInstance(), &VideoCtl::OnPause);
    connect(ui->CtrlBarWid, &CtrlBar::SigStop, VideoCtl::GetInstance(), &VideoCtl::OnStop);
    connect(ui->CtrlBarWid, &CtrlBar::SigBackwardPlay, ui->PlaylistWid, &Playlist::OnBackwardPlay);
    connect(ui->CtrlBarWid, &CtrlBar::SigForwardPlay, ui->PlaylistWid, &Playlist::OnForwardPlay);

    connect(this, &MainWid::SigShowMax, ui->TitleWid, &Title::OnChangeMaxBtnStyle);
    connect(this, &MainWid::SigSeekForward, VideoCtl::GetInstance(), &VideoCtl::OnSeekForward);
    connect(this, &MainWid::SigSeekBack, VideoCtl::GetInstance(), &VideoCtl::OnSeekBack);
    connect(this, &MainWid::SigAddVolume, VideoCtl::GetInstance(), &VideoCtl::OnAddVolume);
    connect(this, &MainWid::SigSubVolume, VideoCtl::GetInstance(), &VideoCtl::OnSubVolume);
    
    connect(VideoCtl::GetInstance(), &VideoCtl::SigVideoTotalSeconds, ui->CtrlBarWid, &CtrlBar::OnVideoTotalSeconds);
    connect(VideoCtl::GetInstance(), &VideoCtl::SigVideoPlaySeconds, ui->CtrlBarWid, &CtrlBar::OnVideoPlaySeconds);
    connect(VideoCtl::GetInstance(), &VideoCtl::SigVideoVolume, ui->CtrlBarWid, &CtrlBar::OnVideopVolume);
    connect(VideoCtl::GetInstance(), &VideoCtl::SigPauseStat, ui->CtrlBarWid, &CtrlBar::OnPauseStat);
    connect(VideoCtl::GetInstance(), &VideoCtl::SigStopFinished, ui->CtrlBarWid, &CtrlBar::OnStopFinished);
    connect(VideoCtl::GetInstance(), &VideoCtl::SigStopFinished, ui->ShowWid, &Show::OnStopFinished);
    connect(VideoCtl::GetInstance(), &VideoCtl::SigStopFinished, ui->TitleWid, &Title::OnStopFinished, Qt::DirectConnection);
    connect(VideoCtl::GetInstance(), &VideoCtl::SigStartPlay, ui->TitleWid, &Title::OnPlay, Qt::DirectConnection);

    //连接信号与槽

    connect(&m_stActionGroup, &QActionGroup::triggered, this, &MainWid::OnActionsTriggered);

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
	case Qt::Key_Return://全屏
        OnFullScreenPlay();
		break;
    case Qt::Key_Left://后退5s
        emit SigSeekBack();
        break;
    case Qt::Key_Right://前进5s
        emit SigSeekForward();
        break;
    case Qt::Key_Up://增加10音量
        emit SigAddVolume();
        break;
    case Qt::Key_Down://减少10音量
        emit SigSubVolume();
        break;
    case Qt::Key_Space://减少10音量
        emit SigPlayOrPause();
        break;
        
	default:
		break;
	}
}


void MainWid::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "MainWid::mouseMoveEvent";
}

void MainWid::contextMenuEvent(QContextMenuEvent* event)
{
    m_stMenu.exec(event->globalPos());
}

void MainWid::OnFullScreenPlay()
{
    qDebug() << "MainWid::OnFullScreenPlay()";
    if (m_bFullScreenPlay == false)
    {
        m_bFullScreenPlay = true;
        //脱离父窗口后才能设置
        ui->ShowWid->setWindowFlags(Qt::Window);
        //多屏情况下，在当前屏幕全屏
        QScreen *pStCurScreen = qApp->screens().at(qApp->desktop()->screenNumber(this));
        ui->ShowWid->windowHandle()->setScreen(pStCurScreen);
        
        ui->ShowWid->showFullScreen();


        QRect stScreenRect = pStCurScreen->geometry();
        int nCtrlBarHeight = ui->CtrlBarWid->height();
        m_stCtrlbarAnimation->setStartValue(QPoint(0, stScreenRect.height()));
        m_stCtrlbarAnimation->setEndValue(QPoint(0, stScreenRect.height() - nCtrlBarHeight * 2));

        m_stCtrlbarAnimation->setDuration(1000);
        m_stCtrlbarAnimation->start();
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
#if 0
    this->showMinimized();
#else
    //ui->CtrlBarWid->setWindowFlags(Qt::Window);
    QScreen *pStCurScreen = qApp->screens().at(qApp->desktop()->screenNumber(this));
    QRect stScreenRect = pStCurScreen->geometry();
    int nCtrlBarHeight = ui->CtrlBarWid->height();
    m_stCtrlbarAnimation->setStartValue(QPoint(0, stScreenRect.height()));
    m_stCtrlbarAnimation->setEndValue(QPoint(0, stScreenRect.height() - nCtrlBarHeight*2));

    m_stCtrlbarAnimation->setDuration(1000);
    m_stCtrlbarAnimation->start();
#endif
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
}

void MainWid::OnActionsTriggered(QAction *action)
{
    QString strAction = action->text();
    if (strAction == "最大化")
    {
        OnMaxBtnClicked();
    }
    else if (strAction == "最小化")
    {
        OnMinBtnClicked();
    }
    else if (strAction == "关闭")
    {
        OnCloseBtnClicked();
    }
}

