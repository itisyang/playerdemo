/*
 * @file 	show.cpp
 * @date 	2018/01/22 23:07
 *
 * @author 	itisyang
 * @Contact	itisyang@gmail.com
 *
 * @brief 	显示控件
 * @note
 */


#include <QDebug>
#include "show.h"
#include "ui_show.h"

#include "globalhelper.h"

#pragma execution_character_set("utf-8")

Show::Show(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Show)
{
    ui->setupUi(this);

    //加载样式
    setStyleSheet(GlobalHelper::GetQssStr(":/Resources/qss/show.css"));
    setAcceptDrops(true);


	
    //防止过度刷新显示
    this->setAttribute(Qt::WA_OpaquePaintEvent);
    //ui->label->setAttribute(Qt::WA_OpaquePaintEvent);


    //this->setMouseTracking(true);
    


    m_nLastFrameWidth = 0; ///< 记录视频宽高
    m_nLastFrameHeight = 0;
}

Show::~Show()
{
    delete ui;
}

bool Show::Init()
{
    if (ConnectSignalSlots() == false)
    {
        return false;
    }

	//ui->label->setUpdatesEnabled(false);

	return true;
}

void Show::AdjustDisplay(int nFrameWidth, int nFrameHeight)
{
    m_nLastFrameWidth = nFrameWidth;
    m_nLastFrameHeight = nFrameHeight;
    
    //qDebug() << nFrameWidth << nFrameHeight;
    if (nFrameWidth == 0 || nFrameHeight == 0)
    {
        return;
//         int w = width();
//         int h = height();
//         ui->label->setGeometry(0, 0, w, h);
    }
	else if (nFrameHeight * width() >= nFrameWidth * height())
	{   //当前供显示的区域，高偏小，以高为标准，高全部显示
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

void Show::dragEnterEvent(QDragEnterEvent *event)
{
//    if(event->mimeData()->hasFormat("text/uri-list"))
//    {
//        event->acceptProposedAction();
//    }
    event->acceptProposedAction();
}

void Show::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    AdjustDisplay(m_nLastFrameWidth, m_nLastFrameHeight);
}

void Show::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Return://全屏
        emit SigFullScreen();
        break;
    default:
        break;
    }
}

// void Show::mouseMoveEvent(QMouseEvent *event)
// {
//     qDebug() << "Show::mouseMoveEvent";
//     setCursor(Qt::ArrowCursor);
//     timerShowCursor.start(1000 * 2);
// }

void Show::OnDisplayMsg(QString strMsg)
{
	qDebug() << "Show::OnDisplayMsg " << strMsg;
}

void Show::OnPlay(QString strFile)
{
	VideoCtl::GetInstance()->StartPlay(strFile, ui->label->winId());
    //VideoCtl::GetInstance()->StartPlay(strFile, this->winId());
}

void Show::OnStopFinished()
{
    update();
}

void Show::OnFrameDimensionsChanged(int nFrameWidth, int nFrameHeight)
{
    AdjustDisplay(nFrameWidth, nFrameHeight);
}

void Show::OnTimerShowCursorUpdate()
{
    setCursor(Qt::BlankCursor);
}

bool Show::ConnectSignalSlots()
{
	QList<bool> listRet;
	bool bRet;

	bRet = connect(this, &Show::SigPlay, this, &Show::OnPlay);
    listRet.append(bRet);

    bRet = connect(&timerShowCursor, &QTimer::timeout, this, &Show::OnTimerShowCursorUpdate);
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

void Show::dropEvent(QDropEvent *event)
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

	//emit SigPlay(urls.first().toLocalFile());
}
