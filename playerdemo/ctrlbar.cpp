/*
 * @file 	ctrlbar.cpp
 * @date 	2018/03/10 22:27
 *
 * @author 	itisyang
 * @Contact	itisyang@gmail.com
 *
 * @brief 	控制界面
 * @note
 */
#include <QDebug>
#include <QSizeGrip>

#include "ctrlbar.h"
#include "ui_ctrlbar.h"

#include "globalhelper.h"

CtrlBar::CtrlBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CtrlBar)
{
    ui->setupUi(this);

    InitUi();
    ConnectSignalSlots();
}

CtrlBar::~CtrlBar()
{
    delete ui;
}

bool CtrlBar::InitUi()
{
    setStyleSheet(GlobalHelper::GetQssStr(":/Resources/qss/ctrlbar.css"));

    GlobalHelper::SetIcon(ui->PlayOrPauseBtn, 12, QChar(0xf04b));
    GlobalHelper::SetIcon(ui->StopBtn, 12, QChar(0xf04d));
    GlobalHelper::SetIcon(ui->VolumeBtn, 12, QChar(0xf028));
    GlobalHelper::SetIcon(ui->PlaylistCtrlBtn, 12, QChar(0xf0ca));
    GlobalHelper::SetIcon(ui->ForwardBtn, 12, QChar(0xf051));
    GlobalHelper::SetIcon(ui->BackwardBtn, 12, QChar(0xf048));
    GlobalHelper::SetIcon(ui->SettingBtn, 12, QChar(0xf013));
    

    return true;

}

bool CtrlBar::ConnectSignalSlots()
{
    QList<bool> listRet;
    bool bRet;


    bRet = connect(ui->PlaylistCtrlBtn, &QPushButton::clicked, this, &CtrlBar::SigShowOrHidePlaylist);
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
