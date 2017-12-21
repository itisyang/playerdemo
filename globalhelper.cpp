
#include <QFile>
#include <QDebug>
#include "globalhelper.h"

GlobalHelper::GlobalHelper()
{

}

QString GlobalHelper::GetQssStr(QString strQssPath)
{
    QString strQss;
    QFile FileQss(strQssPath);
    if (FileQss.open(QIODevice::ReadOnly))
    {
        strQss = FileQss.readAll();
        FileQss.close();
    }
    else
    {
        qDebug() << "获取样式失败" << "样式表：" << strQssPath;
    }
    return strQss;
}

void GlobalHelper::SetIcon(QPushButton* btn, int iconSize, QChar icon)
{
    QFont font;
    font.setFamily("FontAwesome");
    font.setPointSize(iconSize);

    btn->setFont(font);
    btn->setText(icon);
}
