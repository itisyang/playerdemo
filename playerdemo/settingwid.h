#ifndef SETTINGWID_H_
#define SETTINGWID_H_

#include <QWidget>

namespace Ui {
class SettingWid;
}

class SettingWid : public QWidget
{
    Q_OBJECT

public:
    SettingWid(QWidget *parent = Q_NULLPTR);
    ~SettingWid();

private:
    Ui::SettingWid *ui;
};

#endif
