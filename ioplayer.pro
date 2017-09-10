#-------------------------------------------------
#
# Project created by QtCreator 2017-08-24T22:07:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ioplayer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwidget.cpp \
    playlist.cpp \
    title.cpp \
    globalhelper.cpp \
    display.cpp \
    ctrlbar.cpp \
    readthread.cpp \
    videothread.cpp \
    audiothread.cpp \
    subtitlethread.cpp

HEADERS += \
        mainwidget.h \
    playlist.h \
    title.h \
    globalhelper.h \
    display.h \
    ctrlbar.h \
    readthread.h \
    videothread.h \
    audiothread.h \
    subtitlethread.h

FORMS += \
        mainwidget.ui \
    playlist.ui \
    title.ui \
    display.ui \
    ctrlbar.ui

RESOURCES += \
    resource.qrc

INCLUDEPATH += lib/ffmpeg/include

LIBS += -L$$PWD/lib/ffmpeg/lib
LIBS += -lavcodec
LIBS += -lavdevice
LIBS += -lavfilter
LIBS += -lavformat
LIBS += -lavutil
LIBS += -lpostproc
LIBS += -lswresample
LIBS += -lswscale

#win32:LIBS+=\
#-L$$PWD/ffmpeg/lib/-lavcodec-lavdevice-lavfilter-lavformat-lavutil-lpostproc-lswresample-lswscale
