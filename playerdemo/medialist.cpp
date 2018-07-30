#include <QContextMenuEvent>
#include <QFileDialog>

#include "medialist.h"

#pragma execution_character_set("utf-8")

MediaList::MediaList(QWidget *parent)
    : QListWidget(parent),
    m_stMenu(this)
{



}

MediaList::~MediaList()
{
}

bool MediaList::Init()
{
    m_stActAdd.setText("添加");
    m_stMenu.addAction(&m_stActAdd);


    connect(&m_stActAdd, &QAction::triggered, this, &MediaList::AddFile);

    return true;
}

void MediaList::contextMenuEvent(QContextMenuEvent* event)
{
    m_stMenu.exec(event->globalPos());
}

void MediaList::AddFile()
{
    QString strFileName = QFileDialog::getOpenFileName(this, "打开文件", QDir::homePath(),
        "视频文件(*.mkv *.rmvb *.mp4 *.avi *.flv *.wmv *.3gp)");

    emit SigAddFile(strFileName);
}
