#include <QPainter>

#include "title.h"
#include "ui_title.h"

#include "globalhelper.h"

Title::Title(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Title)
{
    ui->setupUi(this);

    //保证窗口不被绘制上的部分透明
    setAttribute(Qt::WA_TranslucentBackground);

    setStyleSheet(GlobalHelper::GetQssStr(":/qss/title.qss"));
    connect(ui->CloseBtn, SIGNAL(clicked(bool)), this, SIGNAL(SigCloseBtnClicked()));
    connect(ui->MinBtn, SIGNAL(clicked(bool)), this, SIGNAL(SigMinBtnClicked()));
    connect(ui->MaxBtn, SIGNAL(clicked(bool)), this, SIGNAL(SigMaxBtnClicked()));
}

Title::~Title()
{
    delete ui;
}


void Title::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

}

void Title::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit SigDoubleClicked();
    }
}

void Title::OnChangeMaxBtnStyle(bool bIfMax)
{
    if (bIfMax)
    {
        ui->MaxBtn->setStyleSheet("QPushButton{image: url(:/res/restore.png);}");
    }
    else
    {
        ui->MaxBtn->setStyleSheet("QPushButton{image: url(:/res/maximize.png);}");
    }

}

