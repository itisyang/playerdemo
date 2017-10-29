#ifndef VIDEODEC_H
#define VIDEODEC_H

#include <QObject>

class VideoDec : public QObject
{
    Q_OBJECT
public:
    explicit VideoDec(QObject *parent = nullptr);

signals:

public slots:
};

#endif // VIDEODEC_H