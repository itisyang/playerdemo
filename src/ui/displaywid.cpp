#include "displaywid.h"
#include "ui_display.h"

#include "globalhelper.h"

DisplayWid::DisplayWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWid)
{
    ui->setupUi(this);

    //加载样式
    setStyleSheet(GlobalHelper::GetQssStr(":/qss/displaywid.css"));
    setAcceptDrops(true);
}

DisplayWid::~DisplayWid()
{
    delete ui;
}

void DisplayWid::dragEnterEvent(QDragEnterEvent *event)
{
//    if(event->mimeData()->hasFormat("text/uri-list"))
//    {
//        event->acceptProposedAction();
//    }
    event->acceptProposedAction();
}

void DisplayWid::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
    {
        return;
    }

    foreach(QUrl url, urls)
    {
        QString strFileName = url.toLocalFile();
        qDebug() << strFileName;
        VideoCtl *pVideoCtl = VideoCtl::GetInstance();
        if (pVideoCtl)
        {
            pVideoCtl->StartPlay(strFileName);
        }

        break;
    }


}
