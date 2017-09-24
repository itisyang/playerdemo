#include <QDebug>

#include "ctrlbar.h"
#include "ui_ctrlbar.h"

#include "globalhelper.h"

CtrlBar::CtrlBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CtrlBar)
{
    ui->setupUi(this);

    InitUi();
}

CtrlBar::~CtrlBar()
{
    delete ui;
}

bool CtrlBar::InitUi()
{
    setStyleSheet(GlobalHelper::GetQssStr(":/qss/ctrlbar.css"));

    GlobalHelper::SetIcon(ui->PlayOrPauseBtn, 20, QChar(0xf01d));
    GlobalHelper::SetIcon(ui->StopBtn, 13, QChar(0xf28e));
    GlobalHelper::SetIcon(ui->VolumeBtn, 12, QChar(0xf028));
    GlobalHelper::SetIcon(ui->MenuBtn, 12, QChar(0xf038));
}
