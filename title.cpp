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
