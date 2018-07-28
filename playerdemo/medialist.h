#pragma once

#include <QListWidget>

class MediaList : public QListWidget
{
    Q_OBJECT

public:
    MediaList(QWidget *parent);
    ~MediaList();
};
