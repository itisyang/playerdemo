#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>

#include "videoctl.h"

namespace Ui {
class DisplayWid;
}

class DisplayWid : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayWid(QWidget *parent = 0);
    ~DisplayWid();

protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
signals:
    void SigAddFile(QString strFileName);///< 增加视频文件
private:
    Ui::DisplayWid *ui;
};

#endif // DISPLAY_H
