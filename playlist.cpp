#include "playlist.h"
#include "ui_playlist.h"

#include "globalhelper.h"

PlayList::PlayList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayList)
{
    ui->setupUi(this);

    setStyleSheet(GlobalHelper::GetQssStr(":/qss/playlist.qss"));

    //ui->List->setFlags(ui->List->flags() & ~Qt::ItemIsSelectable);
}

PlayList::~PlayList()
{
    delete ui;
}
