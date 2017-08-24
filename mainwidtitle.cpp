#include "mainwidtitle.h"
#include "ui_mainwidtitle.h"

MainWidTitle::MainWidTitle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidTitle)
{
    ui->setupUi(this);
}

MainWidTitle::~MainWidTitle()
{
    delete ui;
}
