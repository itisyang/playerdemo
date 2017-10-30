#ifndef GLOBALHELPER_H
#define GLOBALHELPER_H

enum ERROR_CODE
{
    SUCCEED = 0,
    ERROR_FILE_INVALID
};


#include <QString>
#include <QPushButton>

class GlobalHelper
{
public:
    GlobalHelper();
    static QString GetQssStr(QString strQssPath);
    static void    SetIcon(QPushButton* btn, int iconSize, QChar icon);
};

#endif // GLOBALHELPER_H
