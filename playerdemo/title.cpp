/*
 * @file 	title.cpp
 * @date 	2018/01/22 23:08
 *
 * @author 	itisyang
 * @Contact	itisyang@gmail.com
 *
 * @brief 	鎾斁鍣ㄦ爣棰樻爮
 * @note
 */

#include <QPainter>
#include <QFileInfo>

#include "title.h"
#include "ui_title.h"

#include "globalhelper.h"

# pragma execution_character_set("utf-8")

Title::Title(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Title)
{
    ui->setupUi(this);

    connect(ui->CloseBtn, &QPushButton::clicked, this, &Title::SigCloseBtnClicked);
    connect(ui->MinBtn, &QPushButton::clicked, this, &Title::SigMinBtnClicked);
    connect(ui->MaxBtn, &QPushButton::clicked, this, &Title::SigMaxBtnClicked);
    connect(ui->FullScreenBtn, &QPushButton::clicked, this, &Title::SigFullScreenBtnClicked);

    InitUi();
}

Title::~Title()
{
    delete ui;
}

bool Title::InitUi()
{
    ui->MovieNameLab->clear();

    //淇濊瘉绐楀彛涓嶈缁樺埗涓婄殑閮ㄥ垎閫忔槑
    setAttribute(Qt::WA_TranslucentBackground);

    setStyleSheet(GlobalHelper::GetQssStr(":/Resources/qss/title.css"));

    GlobalHelper::SetIcon(ui->MaxBtn, 9, QChar(0xf2d0));
    GlobalHelper::SetIcon(ui->MinBtn, 9, QChar(0xf2d1));
    GlobalHelper::SetIcon(ui->CloseBtn, 9, QChar(0xf00d));

    GlobalHelper::SetIcon(ui->FullScreenBtn, 9, QChar(0xf065));
    
    ui->LogoLab->setToolTip("鑿滃崟");

    return true;
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

void Title::OnChangeMaxBtnStyle(bool bIfMax)
{
    if (bIfMax)
    {
        GlobalHelper::SetIcon(ui->MaxBtn, 9, QChar(0xf2d2));
    }
    else
    {
        GlobalHelper::SetIcon(ui->MaxBtn, 9, QChar(0xf2d0));
    }
}

void Title::OnPlay(QString strMovieName)
{
    QFileInfo fileInfo(strMovieName);
    ui->MovieNameLab->setText(fileInfo.fileName());
}

void Title::OnStopFinished()
{
    ui->MovieNameLab->clear();
}

