#pragma once

#include <QWidget>
#include "ui_settingwid.h"

class SettingWid : public QWidget
{
    Q_OBJECT

public:
    SettingWid(QWidget *parent = Q_NULLPTR);
    ~SettingWid();

private:
    Ui::SettingWid ui;
};
