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

    m_nLastFrameWidth = 0; ///< 记录视频宽高
    m_nLastFrameHeight = 0;
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
    m_nLastFrameWidth = nFrameWidth;
    m_nLastFrameHeight = nFrameHeight;
    qDebug() << "DisplayWid::AdjustDisplay" << nFrameWidth << nFrameHeight;
    if (nFrameWidth == 0 || nFrameHeight == 0)
    {
        qDebug() << "nFrameWidth == 0 || nFrameHeight == 0";
        ui->label->setGeometry(0, 0, width(), height());
    }
	else if (nFrameHeight * width() >= nFrameWidth * height())
	{   //当前供显示的区域，高偏小，以高为标准，高全部显示
        qDebug() << "width() * nFrameHeight >= height() * nFrameWidth";

        int nShowHeight = height();
        int nShowWidth = height() * nFrameWidth / nFrameHeight;
		
        int nY = 0;
        int nX = width() / 2 - nShowWidth / 2;
        
		ui->label->setGeometry(nX, nY, nShowWidth, nShowHeight);
	}
	else
	{   //当前供显示的区域，宽偏小，以宽为标准，宽全部显示
        int nShowWidth = width();
        int nShowHeight = width() * nFrameHeight / nFrameWidth;

        int nX = 0;
        int nY = height() / 2 - nShowHeight / 2;
        
		ui->label->setGeometry(nX, nY, nShowWidth, nShowHeight);
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

void DisplayWid::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    AdjustDisplay(m_nLastFrameWidth, m_nLastFrameHeight);
}

void DisplayWid::OnDisplayMsg(QString strMsg)
{
	qDebug() << "DisplayWid::OnDisplayMsg " << strMsg;
}

void DisplayWid::OnPlay(QString strFile)
{
	VideoCtl::GetInstance()->StartPlay(strFile, ui->label->winId());
}

void DisplayWid::OnFrameDimensionsChanged(int nFrameWidth, int nFrameHeight)
{
    AdjustDisplay(nFrameWidth, nFrameHeight);
}

bool DisplayWid::ConnectSignalSlots()
{
	QList<bool> listRet;
	bool bRet;

	bRet = connect(m_VideoCtl, SIGNAL(SigPlayMsg(QString)), this, SLOT(OnDisplayMsg(QString)));
	listRet.append(bRet);

    bRet = connect(m_VideoCtl, SIGNAL(SigFrameDimensionsChanged(int, int)), this, SLOT(OnFrameDimensionsChanged(int, int)));
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
