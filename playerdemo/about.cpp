#include "about.h"
#include "ui_about.h"

#include "globalhelper.h"

About::About(QWidget *parent)
    : QWidget(parent)
{
    ui = new Ui::About();
    ui->setupUi(this);

}

About::~About()
{
    delete ui;
}

bool About::Init()
{
    this->setWindowModality(Qt::ApplicationModal); //弹出关于窗口，主窗口不可点击

    //this->setWindowIcon(QIcon(":/Resources/player.ico"));
    ui->LogoLabel->setPixmap(QPixmap(":/Resources/player.png").scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    //setStyleSheet(GlobalHelper::GetQssStr(":/Resources/qss/about.css"));

    return true;
}

void About::on_ClosePushButton_clicked()
{
    hide();
}
