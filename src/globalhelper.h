#ifndef GLOBALHELPER_H
#define GLOBALHELPER_H

enum ERROR_CODE
{
    ERROR_NO_ERROR = 0,
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
