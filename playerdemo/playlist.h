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
    bool GetPlaylistStatus();
public slots:
    void OnAddFile(QString strFileName);
signals:
    void SigUpdateUi();
private:
    Ui::Playlist *ui;
};

#endif // PLAYLIST_H
