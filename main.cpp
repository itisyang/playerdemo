#include "mainwidget.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(":/res/fontawesome-webfont.ttf");

    MainWidget w;
    w.show();

    return a.exec();
}
