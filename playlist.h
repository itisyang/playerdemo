#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>

namespace Ui {
class PlayList;
}

class PlayList : public QWidget
{
    Q_OBJECT

public:
    explicit PlayList(QWidget *parent = 0);
    ~PlayList();

private:
    Ui::PlayList *ui;
};

#endif // PLAYLIST_H
