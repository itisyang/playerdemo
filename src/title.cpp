/*
 * @file 	title.cpp
 * @date 	2018/01/22 23:08
 *
 * @author 	itisyang
 * @Contact	itisyang@gmail.com
 *
 * @brief 	播放器标题栏
 * @note
 */

#include <QPainter>
#include <QFileInfo>
#include <QFontMetrics>
#include <QMessageBox>
#include <QFileDialog>

#include "title.h"
#include "ui_title.h"

#include "globalhelper.h"

#pragma execution_character_set("utf-8")

Title::Title(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Title),
    m_stActionGroup(this),
    m_stMenu(this)
{
    ui->setupUi(this);

    //this->setMouseTracking(true);

    connect(ui->CloseBtn, &QPushButton::clicked, this, &Title::SigCloseBtnClicked);
    connect(ui->MinBtn, &QPushButton::clicked, this, &Title::SigMinBtnClicked);
    connect(ui->MaxBtn, &QPushButton::clicked, this, &Title::SigMaxBtnClicked);
    connect(ui->FullScreenBtn, &QPushButton::clicked, this, &Title::SigFullScreenBtnClicked);
    connect(ui->MenuBtn, &QPushButton::clicked, this, &Title::SigShowMenu);
 
    m_stMenu.addAction("最大化", this, &Title::SigMaxBtnClicked);
    m_stMenu.addAction("最小化", this, &Title::SigMinBtnClicked);
    m_stMenu.addAction("退出", this, &Title::SigCloseBtnClicked);

    QMenu* stMenu = m_stMenu.addMenu("打开");
    stMenu->addAction("打开文件", this, &Title::OpenFile);

    ui->MenuBtn->setToolTip("显示主菜单");
    ui->MinBtn->setToolTip("最小化");
    ui->MaxBtn->setToolTip("最大化");
    ui->CloseBtn->setToolTip("关闭");
    ui->FullScreenBtn->setToolTip("全屏");
}

Title::~Title()
{
    delete ui;
}

bool Title::Init()
{
    if (InitUi() == false)
    {
        return false;
    }

    return true;
}

bool Title::InitUi()
{
    ui->MovieNameLab->clear();

    //保证窗口不被绘制上的部分透明
    setAttribute(Qt::WA_TranslucentBackground);

    setStyleSheet(GlobalHelper::GetQssStr("://res/qss/title.css"));

    GlobalHelper::SetIcon(ui->MaxBtn, 9, QChar(0xf2d0));
    GlobalHelper::SetIcon(ui->MinBtn, 9, QChar(0xf2d1));
    GlobalHelper::SetIcon(ui->CloseBtn, 9, QChar(0xf00d));

    GlobalHelper::SetIcon(ui->FullScreenBtn, 9, QChar(0xf065));
    
    //ui->LogoLab->setToolTip("显示主菜单");

    if (about.Init() == false)
    {
        return false;
    }

    return true;
}

void Title::OpenFile()
{
    QString strFileName = QFileDialog::getOpenFileName(this, "打开文件", QDir::homePath(), 
        "视频文件(*.mkv *.rmvb *.mp4 *.avi *.flv *.wmv *.3gp)");

    emit SigOpenFile(strFileName);
}

void Title::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}

void Title::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit SigDoubleClicked();
    }
}

void Title::resizeEvent(QResizeEvent *event)
{
    //ChangeMovieNameShow();
}

// void Title::mouseMoveEvent(QMouseEvent *event)
// {
//     qDebug() << "Title::mouseMoveEvent";
// }

void Title::ChangeMovieNameShow()
{
    QFontMetrics fontMetrics(ui->MovieNameLab->font());
    int fontSize = fontMetrics.width(m_strMovieName);
    int showwidth = ui->MovieNameLab->width();
    if (fontSize > showwidth)
    {
        QString str = fontMetrics.elidedText(m_strMovieName, Qt::ElideRight, ui->MovieNameLab->width());//返回一个带有省略号的字符串
        ui->MovieNameLab->setText(str);
    }
    else
    {
        ui->MovieNameLab->setText(m_strMovieName);
    }
}

void Title::OnChangeMaxBtnStyle(bool bIfMax)
{
    if (bIfMax)
    {
        GlobalHelper::SetIcon(ui->MaxBtn, 9, QChar(0xf2d2));
        ui->MaxBtn->setToolTip("还原");
    }
    else
    {
        GlobalHelper::SetIcon(ui->MaxBtn, 9, QChar(0xf2d0));
        ui->MaxBtn->setToolTip("最大化");
    }
}

void Title::OnPlay(QString strMovieName)
{
    qDebug() << "Title::OnPlay";
    QFileInfo fileInfo(strMovieName);
    m_strMovieName = fileInfo.fileName();
    ui->MovieNameLab->setText(m_strMovieName);
    //ChangeMovieNameShow();
}

void Title::OnStopFinished()
{
    qDebug() << "Title::OnStopFinished";
    ui->MovieNameLab->clear();
}

