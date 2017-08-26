#include <QPainter>

#include "title.h"
#include "ui_title.h"

#include "globalhelper.h"

Title::Title(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Title)
{
    ui->setupUi(this);
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

    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor("#3c4145"));
    p.drawRect(rect());
}

void Title::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit SigDoubleClicked();
    }
}

