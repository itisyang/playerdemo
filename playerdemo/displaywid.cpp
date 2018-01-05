#include <QDebug>
#include "displaywid.h"
#include "ui_display.h"

#include "globalhelper.h"

# pragma execution_character_set("utf-8")

DisplayWid::DisplayWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWid)
{
    ui->setupUi(this);

    //加载样式
    setStyleSheet(GlobalHelper::GetQssStr(":/Resources/qss/displaywid.css"));
    setAcceptDrops(true);

    m_VideoCtl = VideoCtl::GetInstance();
	qRegisterMetaType<QPixmap>("QPixmap&");
    connect(m_VideoCtl, SIGNAL(SigImage(QPixmap&)), this, SLOT(OnImage(QPixmap&)));
	connect(m_VideoCtl, SIGNAL(SigPlayMsg(QString)), this, SLOT(OnDisplayMsg(QString)));
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

void DisplayWid::OnImage(QPixmap& pix)
{
	//qDebug() << pix.width() << pix.height() << pix.size();
	pix = pix.scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	
    ui->label->setPixmap(pix);//播放一帧
	qDebug() << "读取一帧";
	//qDebug() << "获取样式失败" << "播放一帧 ";
}

void DisplayWid::OnDisplayMsg(QString strMsg)
{
	qDebug() << "DisplayWid::OnDisplayMsg " << strMsg;
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
