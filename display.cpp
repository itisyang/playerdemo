#include "display.h"
#include "ui_display.h"

#include "globalhelper.h"

Display::Display(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Display)
{
    ui->setupUi(this);

    //加载样式
    setStyleSheet(GlobalHelper::GetQssStr(":/qss/display.qss"));
}

Display::~Display()
{
    delete ui;
}
