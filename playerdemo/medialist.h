#pragma once

#include <QListWidget>
#include <QMenu>
#include <QAction>

class MediaList : public QListWidget
{
    Q_OBJECT

public:
    MediaList(QWidget *parent);
    ~MediaList();
    bool Init();
protected:
    void contextMenuEvent(QContextMenuEvent* event);
private:
    void AddFile();
signals:
    void SigAddFile(QString strFileName);


private:
    QMenu m_stMenu;

    QAction m_stActAdd;
};
