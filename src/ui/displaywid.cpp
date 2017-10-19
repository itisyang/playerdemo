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
}

DisplayWid::~DisplayWid()
{
    delete ui;
}

void DisplayWid::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat("text/uri-list"))
    {
        event->acceptProposedAction();
    }
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
        QString file_name = url.toLocalFile();
        qDebug() << file_name;
    }
}
