#include "display.h"
#include "ui_display.h"

#include "globalhelper.h"

Display::Display(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Display)
{
    ui->setupUi(this);

    //加载样式
    setStyleSheet(GlobalHelper::GetQssStr(":/qss/display.css"));

    InitFFmpeg();
}

Display::~Display()
{
    delete ui;
}

bool Display::InitFFmpeg()
{
    avdevice_register_all();
    avfilter_register_all();
    av_register_all();
    avformat_network_init();

    return true;
}
void Display::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat("text/uri-list"))
    {
        event->acceptProposedAction();
    }
}

void Display::dropEvent(QDropEvent *event)
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
