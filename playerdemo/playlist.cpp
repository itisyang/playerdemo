#include <QDebug>

#include "playlist.h"
#include "ui_playlist.h"

#include "globalhelper.h"



Playlist::Playlist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Playlist)
{
    ui->setupUi(this);
	Init();
}

Playlist::~Playlist()
{
    delete ui;
}

bool Playlist::Init()
{
	InitUi();
	ConnectSignalSlots();

	return true;
}

bool Playlist::InitUi()
{
    setStyleSheet(GlobalHelper::GetQssStr(":/Resources/qss/playlist.css"));
    //ui->List->hide();
    //this->setFixedWidth(ui->HideOrShowBtn->width());
    //GlobalHelper::SetIcon(ui->HideOrShowBtn, 12, QChar(0xf104));

    ui->List->clear();


	ui->List->addItem("D:/Downloads/地球：神奇的一天.mkv");

    return true;
}

bool Playlist::ConnectSignalSlots()
{
	QList<bool> listRet;
	bool bRet;


	for (bool bReturn : listRet)
	{
		if (bReturn == false)
		{
			return false;
		}
	}

	return true;
}

void Playlist::on_List_itemDoubleClicked(QListWidgetItem *item)
{
	qDebug() << "双击播放：" << item->text();
	emit SigPlay(item->text());
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
	QList<QListWidgetItem *> listItem = ui->List->findItems(strFileName, Qt::MatchExactly);
	if (listItem.isEmpty())
	{
		ui->List->addItem(strFileName);
	}
}
