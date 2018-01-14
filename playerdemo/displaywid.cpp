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

	Init();

}

DisplayWid::~DisplayWid()
{
    delete ui;
}

bool DisplayWid::Init()
{
	ConnectSignalSlots();

	//ui->label->setUpdatesEnabled(false);

	return true;
}

void DisplayWid::dragEnterEvent(QDragEnterEvent *event)
{
//    if(event->mimeData()->hasFormat("text/uri-list"))
//    {
//        event->acceptProposedAction();
//    }
    event->acceptProposedAction();
}

void DisplayWid::OnDisplayMsg(QString strMsg)
{
	qDebug() << "DisplayWid::OnDisplayMsg " << strMsg;
}

void DisplayWid::OnPlay(QString strFile)
{
	if (m_VideoCtl)
	{
		m_VideoCtl->StartPlay(strFile, ui->label->winId());
	}
}

bool DisplayWid::ConnectSignalSlots()
{
	QList<bool> listRet;
	bool bRet;

	qRegisterMetaType<QPixmap>("QPixmap&");
	bRet = connect(m_VideoCtl, SIGNAL(SigImage(QPixmap&)), this, SLOT(OnImage(QPixmap&)), Qt::DirectConnection);
	listRet.append(bRet);
	bRet = connect(m_VideoCtl, SIGNAL(SigPlayMsg(QString)), this, SLOT(OnDisplayMsg(QString)));
	listRet.append(bRet);
	bRet = connect(this, SIGNAL(SigPlay(QString)), this, SLOT(OnPlay(QString)));
	listRet.append(bRet);


	for (bool bReturn : listRet)
	{
		if (bReturn == false)
		{
			return false;
		}
	}

	return true;
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

	emit SigPlay(urls.first().toLocalFile());

}
