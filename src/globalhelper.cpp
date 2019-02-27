#include <QFile>
#include <QDebug>
#include <QSettings>
#include <QCoreApplication>
#include <QDir>

#include "globalhelper.h"

const QString PLAYER_CONFIG_BASEDIR = QDir::tempPath();

const QString PLAYER_CONFIG = "player_config.ini";

const QString APP_VERSION = "0.1.0";

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
        qDebug() << "读取样式表失败" << strQssPath;
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

void GlobalHelper::SavePlaylist(QStringList& playList)
{
    //QString strPlayerConfigFileName = QCoreApplication::applicationDirPath() + QDir::separator() + PLAYER_CONFIG;
    QString strPlayerConfigFileName = PLAYER_CONFIG_BASEDIR + QDir::separator() + PLAYER_CONFIG;
    QSettings settings(strPlayerConfigFileName, QSettings::IniFormat);
    settings.beginWriteArray("playlist");
    for (int i = 0; i < playList.size(); ++i)
    {
        settings.setArrayIndex(i);
        settings.setValue("movie", playList.at(i));
    }
    settings.endArray();
}

void GlobalHelper::GetPlaylist(QStringList& playList)
{
    //QString strPlayerConfigFileName = QCoreApplication::applicationDirPath() + QDir::separator() + PLAYER_CONFIG;
    QString strPlayerConfigFileName = PLAYER_CONFIG_BASEDIR + QDir::separator() + PLAYER_CONFIG;
    QSettings settings(strPlayerConfigFileName, QSettings::IniFormat);

    int size = settings.beginReadArray("playlist");
    for (int i = 0; i < size; ++i) 
    {
        settings.setArrayIndex(i);
        playList.append(settings.value("movie").toString());
    }
    settings.endArray();
}

void GlobalHelper::SavePlayVolume(double& nVolume)
{
    QString strPlayerConfigFileName = PLAYER_CONFIG_BASEDIR + QDir::separator() + PLAYER_CONFIG;
    QSettings settings(strPlayerConfigFileName, QSettings::IniFormat);
    settings.setValue("volume/size", nVolume);
}

void GlobalHelper::GetPlayVolume(double& nVolume)
{
    QString strPlayerConfigFileName = PLAYER_CONFIG_BASEDIR + QDir::separator() + PLAYER_CONFIG;
    QSettings settings(strPlayerConfigFileName, QSettings::IniFormat);
    QString str = settings.value("volume/size").toString();
    nVolume = settings.value("volume/size", nVolume).toDouble();
}

QString GlobalHelper::GetAppVersion()
{
    return APP_VERSION;
}

