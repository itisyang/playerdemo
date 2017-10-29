#ifndef AUDIODEC_H
#define AUDIODEC_H

#include <QObject>

class AudioDec : public QObject
{
    Q_OBJECT
public:
    explicit AudioDec(QObject *parent = nullptr);

signals:

public slots:
};

#endif // AUDIODEC_H