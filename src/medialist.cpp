#include <QContextMenuEvent>
#include <QFileDialog>

#include "medialist.h"

#pragma execution_character_set("utf-8")

MediaList::MediaList(QWidget *parent)
    : QListWidget(parent),
      m_stMenu(this),
      m_stActAdd(this),
      m_stActRemove(this),
      m_stActClearList(this)
{



}

MediaList::~MediaList()
{
}

bool MediaList::Init()
{
    m_stActAdd.setText("添加");
    m_stMenu.addAction(&m_stActAdd);
    m_stActRemove.setText("移除所选项");
    QMenu* stRemoveMenu = m_stMenu.addMenu("移除");
    stRemoveMenu->addAction(&m_stActRemove);
    m_stActClearList.setText("清空列表");
    m_stMenu.addAction(&m_stActClearList);


    connect(&m_stActAdd, &QAction::triggered, this, &MediaList::AddFile);
    connect(&m_stActRemove, &QAction::triggered, this, &MediaList::RemoveFile);
    connect(&m_stActClearList, &QAction::triggered, this, &QListWidget::clear);

    return true;
}

void MediaList::contextMenuEvent(QContextMenuEvent* event)
{
    m_stMenu.exec(event->globalPos());
}

void MediaList::AddFile()
{
    //QList<QUrl> QFileDialog::getOpenFileUrls
    QStringList listFileName = QFileDialog::getOpenFileNames(this, "打开文件", QDir::homePath(),
        "视频文件(*.mkv *.rmvb *.mp4 *.avi *.flv *.wmv *.3gp)");

    for (QString strFileName : listFileName)
    {
        emit SigAddFile(strFileName);
    }
}

void MediaList::RemoveFile()
{
    takeItem(currentRow());
}

