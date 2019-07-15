#pragma once

#include <QListWidget>
#include <QMenu>
#include <QAction>

class MediaList : public QListWidget
{
    Q_OBJECT

public:
    MediaList(QWidget *parent = 0);
    ~MediaList();
    bool Init();
protected:
    void contextMenuEvent(QContextMenuEvent* event);
private:
    void AddFile(); //添加文件
    void RemoveFile();
signals:
    void SigAddFile(QString strFileName);   //添加文件信号


private:
    QMenu m_stMenu;

    QAction m_stActAdd;     //添加文件
    QAction m_stActRemove;  //移除文件
    QAction m_stActClearList;//清空列表
};
