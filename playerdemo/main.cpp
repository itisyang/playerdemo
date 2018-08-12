#include "mainwid.h"
#include <QApplication>
#include <QFontDatabase>

#undef main

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    //使用第三方字库，用来作为UI图片
    QFontDatabase::addApplicationFont(":/Resources/fontawesome-webfont.ttf");
    //QFontDatabase::addApplicationFont(":/Resources/fa-solid-900.ttf");

    MainWid w;
    if (w.Init() == false)
    {
        return -1;
    }
    w.show();

    return a.exec();
}
