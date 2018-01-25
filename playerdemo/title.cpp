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

#include "title.h"
#include "ui_title.h"

#include "globalhelper.h"

Title::Title(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Title)
{
    ui->setupUi(this);

    connect(ui->CloseBtn, SIGNAL(clicked(bool)), this, SIGNAL(SigCloseBtnClicked()));
    connect(ui->MinBtn, SIGNAL(clicked(bool)), this, SIGNAL(SigMinBtnClicked()));
    connect(ui->MaxBtn, SIGNAL(clicked(bool)), this, SIGNAL(SigMaxBtnClicked()));
    connect(ui->FullScreenBtn, SIGNAL(clicked(bool)), this, SIGNAL(SigFullScreenBtnClicked()));

    InitUi();
}

Title::~Title()
{
    delete ui;
}

bool Title::InitUi()
{
    ui->MovieNameLab->clear();

    //保证窗口不被绘制上的部分透明
    setAttribute(Qt::WA_TranslucentBackground);

    setStyleSheet(GlobalHelper::GetQssStr(":/Resources/qss/title.css"));

    GlobalHelper::SetIcon(ui->MaxBtn, 9, QChar(0xf2d0));
    GlobalHelper::SetIcon(ui->MinBtn, 9, QChar(0xf2d1));
    GlobalHelper::SetIcon(ui->CloseBtn, 9, QChar(0xf00d));

    GlobalHelper::SetIcon(ui->FullScreenBtn, 9, QChar(0xf065));
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
        ui->MaxBtn->setText(QChar(0xf2d2));
    }
    else
    {
        ui->MaxBtn->setText(QChar(0xf2d0));
    }
}

