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

void DisplayWid::AdjustDisplay(int nFrameWidth, int nFrameHeight)
{
	if (width() * nFrameHeight >= height() * nFrameWidth)//当前供显示的区域，宽偏小，以宽为标准，宽全部占满
	{
		int nShowWidth = width();
		int nShowHeight = width() * nFrameHeight / nFrameWidth;
		
		int nY = height() / 2 - nShowHeight / 2;
		int nX = 0;
		
		ui->label->setGeometry(nX, nY, nShowWidth, nShowHeight);

	}
	else
	{
// 		int nShowWidth = width();
// 		int nShowHeight = width() * nFrameHeight / nFrameWidth;
// 
// 		int nY = height() / 2 - nShowHeight / 2;
// 		int nX = 0;
// 
// 		ui->label->setGeometry(nX, nY, nShowWidth, nShowHeight);
	}
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
	VideoCtl::GetInstance()->StartPlay(strFile, ui->label->winId());
}

bool DisplayWid::ConnectSignalSlots()
{
	QList<bool> listRet;
	bool bRet;

	bRet = connect(m_VideoCtl, SIGNAL(SigPlayMsg(QString)), this, SLOT(OnDisplayMsg(QString)));
	listRet.append(bRet);
	bRet = connect(this, SIGNAL(SigPlay(QString)), this, SLOT(OnPlay(QString)));
	listRet.append(bRet);

	bRet = connect(this, SIGNAL(SigFullScreen()), m_VideoCtl, SIGNAL(SigFullScreen()));
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
