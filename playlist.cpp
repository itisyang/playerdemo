#include "playlist.h"
#include "ui_playlist.h"

PlayList::PlayList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayList)
{
    ui->setupUi(this);
}

PlayList::~PlayList()
{
    delete ui;
}
