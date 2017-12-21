#include "mainwid.h"
#include <QApplication>
#include <QFontDatabase>

#undef main

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(":/res/fontawesome-webfont.ttf");

    MainWid w;
    w.show();

    return a.exec();
}
