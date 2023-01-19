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
#include <QScreen>
#include <QRect>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>


#include "mainwid.h"
#include "ui_mainwid.h"
#include "globalhelper.h"
#include "videoctl.h"

const int FULLSCREEN_MOUSE_DETECT_TIME = 500;

MainWid::MainWid(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWid),
    m_nShadowWidth(0),
    m_stMenu(this),
    m_stPlaylist(this),
    m_stTitle(this),
    m_bMoveDrag(false),
    m_stActFullscreen(this)
{
    ui->setupUi(this);
    //无边框、无系统菜单、 任务栏点击最小化
    setWindowFlags(Qt::FramelessWindowHint /*| Qt::WindowSystemMenuHint*/ | Qt::WindowMinimizeButtonHint);
    //设置任务栏图标
    this->setWindowIcon(QIcon("://res/player.png"));
    //加载样式
    QString qss = GlobalHelper::GetQssStr("://res/qss/mainwid.css");
    setStyleSheet(qss);

    // 追踪鼠标 用于播放时隐藏鼠标
    this->setMouseTracking(true);

    //ui->ShowWid->setMouseTracking(true);

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

    m_stCtrlBarAnimationTimer.setInterval(2000);
    m_stFullscreenMouseDetectTimer.setInterval(FULLSCREEN_MOUSE_DETECT_TIME);

    
}

MainWid::~MainWid()
{
    delete ui;
}

bool MainWid::Init()
{
    QWidget *em = new QWidget(this);
    ui->PlaylistWid->setTitleBarWidget(em);
    ui->PlaylistWid->setWidget(&m_stPlaylist);
    //ui->PlaylistWid->setFixedWidth(100);

    QWidget *emTitle = new QWidget(this);
    ui->TitleWid->setTitleBarWidget(emTitle);
    ui->TitleWid->setWidget(&m_stTitle);

    //连接自定义信号与槽
    if (ConnectSignalSlots() == false)
    {
        return false;
    }

    if (ui->CtrlBarWid->Init() == false || 
        m_stPlaylist.Init() == false ||
        ui->ShowWid->Init() == false || 
        m_stTitle.Init() == false)
    {
        return false;
    }


    m_stCtrlbarAnimationShow = new QPropertyAnimation(ui->CtrlBarWid, "geometry");
    m_stCtrlbarAnimationHide = new QPropertyAnimation(ui->CtrlBarWid, "geometry");

    if (m_stAboutWidget.Init() == false)
    {
        return false;
    }

    //{
    //    QMenu* menu = AddMenuFun(tr("屏幕"), &m_stMenu);
    //    m_stActFullscreen.setText(tr("全屏"));
    //    m_stActFullscreen.setCheckable(true);
    //    menu->addAction(&m_stActFullscreen);
    //}
    //{
    //    QMenu* menu = AddMenuFun(tr("声音"), &m_stMenu);
    //    AddActionFun(tr("音量 +"), menu, &MainWid::SigAddVolume);
    //    AddActionFun(tr("音量 -"), menu, &MainWid::SigSubVolume);
    //}

    //{
    //    QMenu* menu = AddMenuFun(tr("打开"), &m_stMenu);
    //    AddActionFun(tr("打开文件"), menu, &MainWid::OpenFile);
    //}

    //AddActionFun(tr("关于"), &m_stMenu, &MainWid::OnShowAbout);
    //AddActionFun(tr("退出"), &m_stMenu, &MainWid::OnCloseBtnClicked);


    InitMenu();


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
    //连接信号与槽
	connect(&m_stTitle, &Title::SigCloseBtnClicked, this, &MainWid::OnCloseBtnClicked);
	connect(&m_stTitle, &Title::SigMaxBtnClicked, this, &MainWid::OnMaxBtnClicked);
	connect(&m_stTitle, &Title::SigMinBtnClicked, this, &MainWid::OnMinBtnClicked);
	connect(&m_stTitle, &Title::SigDoubleClicked, this, &MainWid::OnMaxBtnClicked);
    connect(&m_stTitle, &Title::SigFullScreenBtnClicked, this, &MainWid::OnFullScreenPlay);
    connect(&m_stTitle, &Title::SigOpenFile, &m_stPlaylist, &Playlist::OnAddFileAndPlay);
    connect(&m_stTitle, &Title::SigShowMenu, this, &MainWid::OnShowMenu);
    

    connect(&m_stPlaylist, &Playlist::SigPlay, ui->ShowWid, &Show::SigPlay);

	connect(ui->ShowWid, &Show::SigOpenFile, &m_stPlaylist, &Playlist::OnAddFileAndPlay);
    connect(ui->ShowWid, &Show::SigFullScreen, this, &MainWid::OnFullScreenPlay);
    connect(ui->ShowWid, &Show::SigPlayOrPause, VideoCtl::GetInstance(), &VideoCtl::OnPause);
    connect(ui->ShowWid, &Show::SigStop, VideoCtl::GetInstance(), &VideoCtl::OnStop);
    connect(ui->ShowWid, &Show::SigShowMenu, this, &MainWid::OnShowMenu);
    connect(ui->ShowWid, &Show::SigSeekForward, VideoCtl::GetInstance(), &VideoCtl::OnSeekForward);
    connect(ui->ShowWid, &Show::SigSeekBack, VideoCtl::GetInstance(), &VideoCtl::OnSeekBack);
    connect(ui->ShowWid, &Show::SigAddVolume, VideoCtl::GetInstance(), &VideoCtl::OnAddVolume);
    connect(ui->ShowWid, &Show::SigSubVolume, VideoCtl::GetInstance(), &VideoCtl::OnSubVolume);

    connect(ui->CtrlBarWid, &CtrlBar::SigShowOrHidePlaylist, this, &MainWid::OnShowOrHidePlaylist);
    connect(ui->CtrlBarWid, &CtrlBar::SigPlaySeek, VideoCtl::GetInstance(), &VideoCtl::OnPlaySeek);
    connect(ui->CtrlBarWid, &CtrlBar::SigPlayVolume, VideoCtl::GetInstance(), &VideoCtl::OnPlayVolume);
    connect(ui->CtrlBarWid, &CtrlBar::SigPlayOrPause, VideoCtl::GetInstance(), &VideoCtl::OnPause);
    connect(ui->CtrlBarWid, &CtrlBar::SigStop, VideoCtl::GetInstance(), &VideoCtl::OnStop);
    connect(ui->CtrlBarWid, &CtrlBar::SigBackwardPlay, &m_stPlaylist, &Playlist::OnBackwardPlay);
    connect(ui->CtrlBarWid, &CtrlBar::SigForwardPlay, &m_stPlaylist, &Playlist::OnForwardPlay);
    connect(ui->CtrlBarWid, &CtrlBar::SigShowMenu, this, &MainWid::OnShowMenu);
    connect(ui->CtrlBarWid, &CtrlBar::SigShowSetting, this, &MainWid::OnShowSettingWid);

    connect(this, &MainWid::SigShowMax, &m_stTitle, &Title::OnChangeMaxBtnStyle);
    connect(this, &MainWid::SigSeekForward, VideoCtl::GetInstance(), &VideoCtl::OnSeekForward);
    connect(this, &MainWid::SigSeekBack, VideoCtl::GetInstance(), &VideoCtl::OnSeekBack);
    connect(this, &MainWid::SigAddVolume, VideoCtl::GetInstance(), &VideoCtl::OnAddVolume);
    connect(this, &MainWid::SigSubVolume, VideoCtl::GetInstance(), &VideoCtl::OnSubVolume);
    connect(this, &MainWid::SigOpenFile, &m_stPlaylist, &Playlist::OnAddFileAndPlay);
    
    
    connect(VideoCtl::GetInstance(), &VideoCtl::SigVideoTotalSeconds, ui->CtrlBarWid, &CtrlBar::OnVideoTotalSeconds);
    connect(VideoCtl::GetInstance(), &VideoCtl::SigVideoPlaySeconds, ui->CtrlBarWid, &CtrlBar::OnVideoPlaySeconds);
    connect(VideoCtl::GetInstance(), &VideoCtl::SigVideoVolume, ui->CtrlBarWid, &CtrlBar::OnVideopVolume);
    connect(VideoCtl::GetInstance(), &VideoCtl::SigPauseStat, ui->CtrlBarWid, &CtrlBar::OnPauseStat, Qt::QueuedConnection);
    connect(VideoCtl::GetInstance(), &VideoCtl::SigStopFinished, ui->CtrlBarWid, &CtrlBar::OnStopFinished, Qt::QueuedConnection);
    connect(VideoCtl::GetInstance(), &VideoCtl::SigStopFinished, ui->ShowWid, &Show::OnStopFinished, Qt::QueuedConnection);
    connect(VideoCtl::GetInstance(), &VideoCtl::SigFrameDimensionsChanged, ui->ShowWid, &Show::OnFrameDimensionsChanged, Qt::QueuedConnection);
    connect(VideoCtl::GetInstance(), &VideoCtl::SigStopFinished, &m_stTitle, &Title::OnStopFinished, Qt::DirectConnection);
    connect(VideoCtl::GetInstance(), &VideoCtl::SigStartPlay, &m_stTitle, &Title::OnPlay, Qt::DirectConnection);

    connect(&m_stCtrlBarAnimationTimer, &QTimer::timeout, this, &MainWid::OnCtrlBarAnimationTimeOut);

    connect(&m_stFullscreenMouseDetectTimer, &QTimer::timeout, this, &MainWid::OnFullscreenMouseDetectTimeOut);


    connect(&m_stActFullscreen, &QAction::triggered, this, &MainWid::OnFullScreenPlay);
    


	return true;
}


void MainWid::keyReleaseEvent(QKeyEvent *event)
{
// 	    // 是否按下Ctrl键      特殊按键
//     if(event->modifiers() == Qt::ControlModifier){
//         // 是否按下M键    普通按键  类似
//         if(event->key() == Qt::Key_M)
//             ···
//     }
    qDebug() << "MainWid::keyPressEvent:" << event->key();
	switch (event->key())
	{
	case Qt::Key_Return://全屏
        OnFullScreenPlay();
		break;
    case Qt::Key_Left://后退5s
        emit SigSeekBack();
        break;
    case Qt::Key_Right://前进5s
        qDebug() << "前进5s";
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


void MainWid::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (ui->TitleWid->geometry().contains(event->pos()))
        {
            m_bMoveDrag = true;
            m_DragPosition = event->globalPos() - this->pos();
        }
    }

    QWidget::mousePressEvent(event);
}

void MainWid::mouseReleaseEvent(QMouseEvent *event)
{
    m_bMoveDrag = false;

    QWidget::mouseReleaseEvent(event);
}

void MainWid::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bMoveDrag)
    {
        move(event->globalPos() - m_DragPosition);
    }

    QWidget::mouseMoveEvent(event);
}

void MainWid::contextMenuEvent(QContextMenuEvent* event)
{
    m_stMenu.exec(event->globalPos());
}

void MainWid::OnFullScreenPlay()
{
    if (m_bFullScreenPlay == false)
    {
        m_bFullScreenPlay = true;
        m_stActFullscreen.setChecked(true);
        //脱离父窗口后才能设置
        ui->ShowWid->setWindowFlags(Qt::Window);
        //多屏情况下，在当前屏幕全屏
        QScreen *pStCurScreen = screen();
        ui->ShowWid->windowHandle()->setScreen(pStCurScreen);
        
        ui->ShowWid->showFullScreen();


        QRect stScreenRect = pStCurScreen->geometry();
        int nCtrlBarHeight = ui->CtrlBarWid->height();
        int nX = ui->ShowWid->x();
        m_stCtrlBarAnimationShow = QRect(nX, stScreenRect.height() - nCtrlBarHeight, stScreenRect.width(), nCtrlBarHeight);
        m_stCtrlBarAnimationHide = QRect(nX, stScreenRect.height(), stScreenRect.width(), nCtrlBarHeight);

        m_stCtrlbarAnimationShow->setStartValue(m_stCtrlBarAnimationHide);
        m_stCtrlbarAnimationShow->setEndValue(m_stCtrlBarAnimationShow);
        m_stCtrlbarAnimationShow->setDuration(1000);

        m_stCtrlbarAnimationHide->setStartValue(m_stCtrlBarAnimationShow);
        m_stCtrlbarAnimationHide->setEndValue(m_stCtrlBarAnimationHide);
        m_stCtrlbarAnimationHide->setDuration(1000);
        
        ui->CtrlBarWid->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
        ui->CtrlBarWid->windowHandle()->setScreen(pStCurScreen);
        ui->CtrlBarWid->raise();
        ui->CtrlBarWid->setWindowOpacity(0.5);
        ui->CtrlBarWid->showNormal();
        ui->CtrlBarWid->windowHandle()->setScreen(pStCurScreen);
        
        m_stCtrlbarAnimationShow->start();
        m_bFullscreenCtrlBarShow = true;
        m_stFullscreenMouseDetectTimer.start();

        this->setFocus();
    }
    else
    {
        m_bFullScreenPlay = false;
        m_stActFullscreen.setChecked(false);

        m_stCtrlbarAnimationShow->stop(); //快速切换时，动画还没结束导致控制面板消失
        m_stCtrlbarAnimationHide->stop();
        ui->CtrlBarWid->setWindowOpacity(1);
        ui->CtrlBarWid->setWindowFlags(Qt::SubWindow);
        
        ui->ShowWid->setWindowFlags(Qt::SubWindow);

        ui->CtrlBarWid->showNormal();
        ui->ShowWid->showNormal();

        m_stFullscreenMouseDetectTimer.stop();
        this->setFocus();
    }
}

void MainWid::OnCtrlBarAnimationTimeOut()
{
    QApplication::setOverrideCursor(Qt::BlankCursor);
}

void MainWid::OnFullscreenMouseDetectTimeOut()
{
//     qDebug() << m_stCtrlBarAnimationShow;
//     qDebug() << cursor().pos();
//     qDebug() << ui->CtrlBarWid->geometry();
    if (m_bFullScreenPlay)
    {
        if (m_stCtrlBarAnimationShow.contains(cursor().pos()))
        {
            //判断鼠标是否在控制面板上面
            if (ui->CtrlBarWid->geometry().contains(cursor().pos()))
            {
                //继续显示
                m_bFullscreenCtrlBarShow = true;
            }
            else
            {
                //需要显示
                ui->CtrlBarWid->raise();
                
                m_stCtrlbarAnimationShow->start();
                m_stCtrlbarAnimationHide->stop();
                stCtrlBarHideTimer.stop();
            }
        }
        else  
        {
            if (m_bFullscreenCtrlBarShow)
            {
                //需要隐藏
                m_bFullscreenCtrlBarShow = false;
                stCtrlBarHideTimer.singleShot(2000, this, &MainWid::OnCtrlBarHideTimeOut);
            }

        }

    }
}

void MainWid::OnCtrlBarHideTimeOut()
{
    if (m_bFullScreenPlay)
    {
        m_stCtrlbarAnimationHide->start();
    }
    //setCursor(Qt::BlankCursor);

}

void MainWid::OnShowMenu()
{
    m_stMenu.exec(cursor().pos());
}

void MainWid::OnShowAbout()
{
    m_stAboutWidget.move(cursor().pos().x() - m_stAboutWidget.width()/2, cursor().pos().y() - m_stAboutWidget.height()/2);
    m_stAboutWidget.show();
}

void MainWid::OpenFile()
{
    QString strFileName = QFileDialog::getOpenFileName(this, "打开文件", QDir::homePath(),
        "视频文件(*.mkv *.rmvb *.mp4 *.avi *.flv *.wmv *.3gp)");

    emit SigOpenFile(strFileName);
}

void MainWid::OnShowSettingWid()
{
    m_stSettingWid.show();
}

void MainWid::InitMenu()
{
    QString menu_json_file_name = ":/res/menu.json";
    QByteArray ba_json;
    QFile json_file(menu_json_file_name);
    if (json_file.open(QIODevice::ReadOnly))
    {
        ba_json = json_file.readAll();
        json_file.close();
    }

    QJsonDocument json_doc = QJsonDocument::fromJson(ba_json);

    if (json_doc.isObject())
    {
        QJsonObject json_obj = json_doc.object();
        MenuJsonParser(json_obj, &m_stMenu);
    }

}

void MainWid::MenuJsonParser(QJsonObject& json_obj, QMenu* menu)
{
    QJsonObject::iterator it = json_obj.begin();
    QJsonObject::iterator end = json_obj.end();
    while (it != end)
    {
        QString key = it.key();
        auto value = it.value();
        if (value.isObject())
        {
            QMenu* sub_menu = menu->addMenu(key);
            QJsonObject obj = value.toObject();
            MenuJsonParser(obj, sub_menu);
        }
        else
        {
            QString value_str = value.toString();
            QStringList value_info = value_str.split("/");
            if (value_info.size() == 2)
            {
                QString hot_key = value_info[1];
                if (hot_key.length() > 0)
                {
                    key = key + "\t" + hot_key;
                }
                QAction* action = menu->addAction(key);

                //TODO: 字符串与函数指针对应，连接信号
                QString fun_str = value_info[0];


            }
        }

        it++;
    }
}

QMenu* MainWid::AddMenuFun(QString menu_title, QMenu* menu)
{
    QMenu* menu_t = new QMenu(this);
    menu_t->setTitle(menu_title);
    menu->addMenu(menu_t);
    return menu_t;
}

void MainWid::AddActionFun(QString action_title, QMenu* menu, void(MainWid::* slot_addr)())
{
    QAction* action = new QAction(this);;
    action->setText(action_title);
    menu->addAction(action);
    connect(action, &QAction::triggered, this, slot_addr);
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
}
