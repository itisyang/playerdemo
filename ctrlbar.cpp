#include "ctrlbar.h"
#include "ui_ctrlbar.h"

CtrlBar::CtrlBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CtrlBar)
{
    ui->setupUi(this);
}

CtrlBar::~CtrlBar()
{
    delete ui;
}
