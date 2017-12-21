#ifndef PLAYLISTCTRLBAR_H
#define PLAYLISTCTRLBAR_H

#include <QWidget>

namespace Ui {
class PlaylistCtrlBar;
}

class PlaylistCtrlBar : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistCtrlBar(QWidget *parent = 0);
    ~PlaylistCtrlBar();

private slots:
    void on_ShowOrHideBtn_clicked();
signals:
    void SigShowOrHidePlaylist();
private:
    Ui::PlaylistCtrlBar *ui;
};

#endif // PLAYLISTCTRLBAR_H
