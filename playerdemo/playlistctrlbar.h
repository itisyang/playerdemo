/*
 * @file 	playlistctrlbar.h
 * @date 	2018/01/07 11:13
 *
 * @author 	itisyang
 * @Contact	itisyang@gmail.com
 *
 * @brief 	播放列表控制控件(控制隐藏或显示)
 * @note
 */
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
    void SigShowOrHidePlaylist();	//< 显示或隐藏信号
private:
    Ui::PlaylistCtrlBar *ui;
};

#endif // PLAYLISTCTRLBAR_H
