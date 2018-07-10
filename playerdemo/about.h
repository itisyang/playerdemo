#pragma once

#include <QWidget>
namespace Ui { class About; };

class About : public QWidget
{
    Q_OBJECT

public:
    About(QWidget *parent = Q_NULLPTR);
    ~About();
    bool Init();
 private slots:
    void on_ClosePushButton_clicked();
private:
    Ui::About *ui;
};
