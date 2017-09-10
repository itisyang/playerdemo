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

    InitFFmpeg();
}

Display::~Display()
{
    delete ui;
}

bool Display::InitFFmpeg()
{
    avdevice_register_all();
    avfilter_register_all();
    av_register_all();
    avformat_network_init();

    return true;
}
