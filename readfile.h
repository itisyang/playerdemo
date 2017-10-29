#ifndef READFILE_H
#define READFILE_H

#include <QObject>

class ReadFile : public QObject
{
    Q_OBJECT
public:
    explicit ReadFile(QObject *parent = nullptr);

signals:

public slots:
};

#endif // READFILE_H