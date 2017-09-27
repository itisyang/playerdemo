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

    InitFFmpeg();
}

DisplayWid::~DisplayWid()
{
    delete ui;
}

bool DisplayWid::InitFFmpeg()
{
    avdevice_register_all();
    avfilter_register_all();
    av_register_all();
    avformat_network_init();

    return true;
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
