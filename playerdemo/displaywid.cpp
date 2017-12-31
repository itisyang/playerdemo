#include "displaywid.h"
#include "ui_display.h"

#include "globalhelper.h"

DisplayWid::DisplayWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWid)
{
    ui->setupUi(this);

    //加载样式
    setStyleSheet(GlobalHelper::GetQssStr(":/Resources/qss/displaywid.css"));
    setAcceptDrops(true);

    m_VideoCtl = VideoCtl::GetInstance();
    connect(m_VideoCtl, SIGNAL(SigImage(QImage&)), this, SLOT(OnImage(QImage &)));
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

void DisplayWid::OnImage(QImage &image)
{
    QPixmap pix = QPixmap::fromImage(image).scaled(ui->label->width(),
                                           ui->label->height(),
                                           Qt::KeepAspectRatio,
                                           Qt::SmoothTransformation);
    ui->label->setPixmap(pix);
}

void DisplayWid::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
    {
        return;
    }

    for(QUrl url: urls)
    {
        QString strFileName = url.toLocalFile();
        qDebug() << strFileName;
        emit SigAddFile(strFileName);
        break;
    }

    if (m_VideoCtl)
    {
        m_VideoCtl->StartPlay(urls.first().toLocalFile());
    }



}
