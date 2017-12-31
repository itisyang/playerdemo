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
    setStyleSheet(GlobalHelper::GetQssStr(":/Resources/qss/playlist.css"));
    //ui->List->hide();
    //this->setFixedWidth(ui->HideOrShowBtn->width());
    //GlobalHelper::SetIcon(ui->HideOrShowBtn, 12, QChar(0xf104));

    ui->List->clear();

    return true;
}

bool Playlist::GetPlaylistStatus()
{
    if (this->isHidden())
    {
        return false;
    }

    return true;
}

void Playlist::OnAddFile(QString strFileName)
{
    ui->List->addItem(strFileName);
}
