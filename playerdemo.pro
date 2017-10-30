#-------------------------------------------------
#
# Project created by QtCreator 2017-08-24T22:07:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = playerdemo
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

INCLUDEPATH += lib/sdl/include/SDL2
LIBS += -L$$PWD/lib/sdl/lib
LIBS += -lSDL2

RESOURCES += \
    resource.qrc

FORMS += \
    src/ui/ctrlbar.ui \
    src/ui/display.ui \
    src/ui/mainwid.ui \
    src/ui/playlist.ui \
    src/ui/title.ui

INCLUDEPATH += src/ \
    src/ui/

HEADERS += \
    src/ui/ctrlbar.h \
    src/globalhelper.h \
    src/ui/mainwid.h \
    src/ui/playlist.h \
    src/ui/title.h \
    src/ui/displaywid.h \
    src/ui/framelesshelper.h \
    readfile.h \
    videodec.h \
    subtitledec.h \
    audiodec.h \
    videostate.h

SOURCES += \
    src/ui/ctrlbar.cpp \
    src/globalhelper.cpp \
    src/main.cpp \
    src/ui/mainwid.cpp \
    src/ui/playlist.cpp \
    src/ui/title.cpp \
    src/ui/displaywid.cpp \
    src/ui/framelesshelper.cpp \
    readfile.cpp \
    videodec.cpp \
    subtitledec.cpp \
    audiodec.cpp \
    videostate.cpp
