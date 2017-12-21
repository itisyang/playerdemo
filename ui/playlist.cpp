#include "playlist.h"
#include "ui_playlist.h"

#include "globalhelper.h"

Playlist::Playlist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Playlist)
{
    ui->setupUi(this);
    InitUi();
}

Playlist::~Playlist()
{
    delete ui;
}

bool Playlist::InitUi()
{
    setStyleSheet(GlobalHelper::GetQssStr(":/qss/playlist.css"));
    ui->List->hide();
    //this->setFixedWidth(ui->HideOrShowBtn->width());
    GlobalHelper::SetIcon(ui->HideOrShowBtn, 12, QChar(0xf104));

    return true;
}

bool Playlist::GetPlaylistStatus()
{
    if (ui->List->isHidden())
    {
        return false;
    }

    return true;
}

void Playlist::on_HideOrShowBtn_clicked()
{
    if (ui->List->isHidden())
    {
        ui->List->show();
        //this->setFixedWidth(ui->HideOrShowBtn->width() + ui->List->width());
        GlobalHelper::SetIcon(ui->HideOrShowBtn, 12, QChar(0xf105));
    }
    else
    {
        ui->List->hide();
        //this->setFixedWidth(ui->HideOrShowBtn->width());
        GlobalHelper::SetIcon(ui->HideOrShowBtn, 12, QChar(0xf104));
    }

    emit SigUpdateUi();
}
