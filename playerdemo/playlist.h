/*
 * @file 	playlist.h
 * @date 	2018/01/07 11:12
 *
 * @author 	itisyang
 * @Contact	itisyang@gmail.com
 *
 * @brief 	播放列表控件
 * @note
 */
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>
#include <QListWidgetItem>
namespace Ui {
class Playlist;
}

class Playlist : public QWidget
{
    Q_OBJECT

public:
    explicit Playlist(QWidget *parent = 0);
    ~Playlist();

	bool Init();


	/**
	 * @brief	获取播放列表状态
	 * 
	 * @return	true 显示 false 隐藏
	 * @note 	
	 */
    bool GetPlaylistStatus();
public slots:
	/**
	 * @brief	添加文件
	 * 
	 * @param	strFileName 文件完整路径
	 * @note 	
	 */
    void OnAddFile(QString strFileName);
signals:
    void SigUpdateUi();	//< 界面排布更新
	void SigPlay(QString strFile); //< 播放文件
private:
	bool InitUi();
	bool ConnectSignalSlots();
private slots:
	void on_List_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::Playlist *ui;
};

#endif // PLAYLIST_H
