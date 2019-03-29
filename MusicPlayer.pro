#-------------------------------------------------
#
# Project created by QtCreator 2019-03-28T20:33:46
#
#-------------------------------------------------

QT       += core gui
QT += multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MusicPlayer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        src/main.cpp \
    src/controller/musicplayercontroller.cpp \
    src/model/musicplayermodel.cpp \
    src/controller/playfunccontroller.cpp \
    src/controller/lyricscontroller.cpp \
    src/model/playfuncmodel.cpp \
    src/view/playfuncview.cpp \
    src/view/musicplayerview.cpp \
    src/view/mainwindow.cpp \
    src/controller/mainwindowcontroller.cpp \
    src/model/mainwindowmodel.cpp


HEADERS += \
    src/controller/musicplayercontroller.h \
    src/model/musicplayermodel.h \
    src/controller/playfunccontroller.h \
    src/controller/lyricscontroller.h \
    src/model/playfuncmodel.h \
    src/view/playfuncview.h \
    src/view/musicplayerview.h \
    src/view/mainwindow.h \
    src/model/mainwindowmodel.h \
    src/controller/mainwindowcontroller.h

FORMS += \
    src/view/playfuncview.ui \
    src/view/musicplayerview.ui \
    src/view/mainwindow.ui

DISTFILES += \
    src/document

RESOURCES += \
    resources/uiresources.qrc

INCLUDEPATH += $$PWD/src/
INCLUDEPATH += $$PWD/src/controller/
INCLUDEPATH += $$PWD/src/model/
INCLUDEPATH += $$PWD/src/view/

