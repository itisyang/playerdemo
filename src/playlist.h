#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>

namespace Ui {
class Playlist;
}

class Playlist : public QWidget
{
    Q_OBJECT

public:
    explicit Playlist(QWidget *parent = 0);
    ~Playlist();

    bool InitUi();

private slots:
    void on_HideOrShowBtn_clicked();

private:
    Ui::Playlist *ui;
};

#endif // PLAYLIST_H
