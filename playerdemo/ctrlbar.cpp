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
#include <QTime>
#include <QSettings>
 
#include "ctrlbar.h"
#include "ui_ctrlbar.h"

#include "globalhelper.h"

CtrlBar::CtrlBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CtrlBar)
{
    ui->setupUi(this);

    m_dLastVolumePercent = 1.0;

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
    GlobalHelper::SetIcon(ui->PlaylistCtrlBtn, 20, QChar(0xf0ca));
    GlobalHelper::SetIcon(ui->ForwardBtn, 12, QChar(0xf051));
    GlobalHelper::SetIcon(ui->BackwardBtn, 12, QChar(0xf048));
    GlobalHelper::SetIcon(ui->SettingBtn, 12, QChar(0xf013));
    


    return true;

}

bool CtrlBar::ConnectSignalSlots()
{
    QList<bool> listRet;
    bool bRet;


    connect(ui->PlaylistCtrlBtn, &QPushButton::clicked, this, &CtrlBar::SigShowOrHidePlaylist);
    connect(ui->PlaySlider, &CustomSlider::SigCustomSliderValueChanged, this, &CtrlBar::OnPlaySliderValueChanged);
    connect(ui->VolumeSlider, &CustomSlider::SigCustomSliderValueChanged, this, &CtrlBar::OnVolumeSliderValueChanged);
    
    return true;
}

void CtrlBar::OnVideoTotalSeconds(int nSeconds)
{
    m_nTotalPlaySeconds = nSeconds;

    int thh, tmm, tss;
    thh = nSeconds / 3600;
    tmm = (nSeconds % 3600) / 60;
    tss = (nSeconds % 60);
    QTime TotalTime(thh, tmm, tss);

    ui->VideoTotalTimeTimeEdit->setTime(TotalTime);
}


void CtrlBar::OnVideoPlaySeconds(int nSeconds)
{
    int thh, tmm, tss;
    thh = nSeconds / 3600;
    tmm = (nSeconds % 3600) / 60;
    tss = (nSeconds % 60);
    QTime TotalTime(thh, tmm, tss);

    ui->VideoPlayTimeTimeEdit->setTime(TotalTime);

    ui->PlaySlider->setValue(nSeconds * 1.0 / m_nTotalPlaySeconds * MAX_SLIDER_VALUE);
}

void CtrlBar::OnVideopVolume(double dPercent)
{
    ui->VolumeSlider->setValue(dPercent * MAX_SLIDER_VALUE);
    m_dLastVolumePercent = dPercent;

    if (m_dLastVolumePercent == 0)
    {
        GlobalHelper::SetIcon(ui->VolumeBtn, 12, QChar(0xf026));
    }
    else
    {
        GlobalHelper::SetIcon(ui->VolumeBtn, 12, QChar(0xf028));
    }
}

void CtrlBar::OnPauseStat(bool bPaused)
{
    if (bPaused)
    {
        GlobalHelper::SetIcon(ui->PlayOrPauseBtn, 12, QChar(0xf04b));
    }
    else
    {
        GlobalHelper::SetIcon(ui->PlayOrPauseBtn, 12, QChar(0xf04c));
    }
}

void CtrlBar::OnStopFinished()
{
    ui->PlaySlider->setValue(0);
}

void CtrlBar::OnPlaySliderValueChanged()
{
    double dPercent = ui->PlaySlider->value()*1.0 / ui->PlaySlider->maximum();
    emit SigPlaySeek(dPercent);
    m_dLastVolumePercent = dPercent;

    if (m_dLastVolumePercent == 0)
    {
        GlobalHelper::SetIcon(ui->VolumeBtn, 12, QChar(0xf026));
    }
    else
    {
        GlobalHelper::SetIcon(ui->VolumeBtn, 12, QChar(0xf028));
    }
}

void CtrlBar::OnVolumeSliderValueChanged()
{
    double dPercent = ui->VolumeSlider->value()*1.0 / ui->VolumeSlider->maximum();
    emit SigPlayVolume(dPercent);
    m_dLastVolumePercent = dPercent;

    if (m_dLastVolumePercent == 0)
    {
        GlobalHelper::SetIcon(ui->VolumeBtn, 12, QChar(0xf026));
    }
    else
    {
        GlobalHelper::SetIcon(ui->VolumeBtn, 12, QChar(0xf028));
    }
}

void CtrlBar::on_PlayOrPauseBtn_clicked()
{
    emit SigPause();
}

void CtrlBar::on_VolumeBtn_clicked()
{
    if (ui->VolumeBtn->text() == QChar(0xf028))
    {
        GlobalHelper::SetIcon(ui->VolumeBtn, 12, QChar(0xf026));
        ui->VolumeSlider->setValue(0);
        emit SigPlayVolume(0);
    }
    else
    {
        GlobalHelper::SetIcon(ui->VolumeBtn, 12, QChar(0xf028));
        ui->VolumeSlider->setValue(m_dLastVolumePercent * MAX_SLIDER_VALUE);
        OnVideopVolume(m_dLastVolumePercent);
        emit SigPlayVolume(m_dLastVolumePercent);
    }
}

void CtrlBar::on_StopBtn_clicked()
{
    emit SigStop();
}

