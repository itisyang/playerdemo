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

    //this->setWindowFlags(Qt::Dialog);

    this->setWindowIcon(QIcon(":/Resources/player.png"));
    ui->LogoLabel->setPixmap(QPixmap(":/Resources/player.png").scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    //setStyleSheet(GlobalHelper::GetQssStr(":/Resources/qss/about.css"));

    QString strVersion = QString("版本：%1\n时间：%2").arg(GlobalHelper::GetAppVersion()).arg(QString(__DATE__) + " " + QString(__TIME__));
    ui->VersionLabel->setText(strVersion);


    return true;
}

void About::on_ClosePushButton_clicked()
{
    hide();
}
