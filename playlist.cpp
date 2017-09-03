#include "playlist.h"
#include "ui_playlist.h"

#include "globalhelper.h"

Playlist::Playlist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Playlist)
{
    ui->setupUi(this);

    setStyleSheet(GlobalHelper::GetQssStr(":/qss/playlist.qss"));
    ui->List->hide();
}

Playlist::~Playlist()
{
    delete ui;
}

void Playlist::on_HideOrShowBtn_clicked()
{
    if (ui->List->isHidden())
    {
        ui->List->show();
    }
    else
    {
        ui->List->hide();
    }
}
