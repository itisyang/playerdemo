#pragma once

#include <QListWidget>

class MediaList : public QListWidget
{
    Q_OBJECT

public:
    MediaList(QObject *parent);
    ~MediaList();
};
