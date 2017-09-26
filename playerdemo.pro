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

RESOURCES += \
    resource.qrc

FORMS += \
    src/ctrlbar.ui \
    src/display.ui \
    src/mainwidget.ui \
    src/playlist.ui \
    src/title.ui

HEADERS += \
    src/audiothread.h \
    src/ctrlbar.h \
    src/display.h \
    src/globalhelper.h \
    src/mainwidget.h \
    src/playlist.h \
    src/readthread.h \
    src/subtitlethread.h \
    src/title.h \
    src/videothread.h

SOURCES += \
    src/audiothread.cpp \
    src/ctrlbar.cpp \
    src/display.cpp \
    src/globalhelper.cpp \
    src/main.cpp \
    src/mainwidget.cpp \
    src/playlist.cpp \
    src/readthread.cpp \
    src/subtitlethread.cpp \
    src/title.cpp \
    src/videothread.cpp
