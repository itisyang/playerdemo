#-------------------------------------------------
#
# Project created by QtCreator 2017-08-24T22:07:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = playerdemo
TEMPLATE = app

win32:debug{
CONFIG += console
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#INCLUDEPATH += lib/ffmpeg/include
#LIBS += -L$$PWD/lib/ffmpeg/lib
#LIBS += -lavcodec
#LIBS += -lavdevice
#LIBS += -lavfilter
#LIBS += -lavformat
#LIBS += -lavutil
#LIBS += -lpostproc
#LIBS += -lswresample
#LIBS += -lswscale

#INCLUDEPATH += lib/sdl/include/SDL2
#LIBS += -L$$PWD/lib/sdl/lib
#LIBS += -llibSDL2

INCLUDEPATH += \
    lib/ffmpeg/include \
    lib/sdl/include \

win32: LIBS += \
    -L$$PWD/lib/ffmpeg/lib -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lswresample -lswscale \
    -L$$PWD/lib/sdl/lib/x86 -lSDL2 \


RESOURCES += \
    resource.qrc

FORMS += \
    ui/ctrlbar.ui \
    ui/display.ui \
    ui/mainwid.ui \
    ui/playlist.ui \
    ui/title.ui \
    ui/playlistctrlbar.ui

INCLUDEPATH +=  \
    ui/

HEADERS += \
    ui/ctrlbar.h \
    globalhelper.h \
    ui/mainwid.h \
    ui/playlist.h \
    ui/title.h \
    ui/displaywid.h \
    ui/framelesshelper.h \
    readfile.h \
    videodec.h \
    subtitledec.h \
    audiodec.h \
    videoctl.h \
    videodataoprator.h \
    customthread.h \
    ui/playlistctrlbar.h

SOURCES += \
    ui/ctrlbar.cpp \
    globalhelper.cpp \
    main.cpp \
    ui/mainwid.cpp \
    ui/playlist.cpp \
    ui/title.cpp \
    ui/displaywid.cpp \
    ui/framelesshelper.cpp \
    readfile.cpp \
    videodec.cpp \
    subtitledec.cpp \
    audiodec.cpp \
    videoctl.cpp \
    videodataoprator.cpp \
    customthread.cpp \
    ui/playlistctrlbar.cpp
