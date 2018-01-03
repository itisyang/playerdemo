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
    connect(m_VideoCtl, SIGNAL(SigImage(QPixmap)), this, SLOT(OnImage(QPixmap)));
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

void DisplayWid::OnImage(QPixmap pix)
{
	//qDebug() << pix.width() << pix.height() << pix.size();
	pix = pix.scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->label->setPixmap(pix);
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
