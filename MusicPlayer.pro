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
    src/controller/downloadcontroller.cpp \
    src/controller/localmusiccontroller.cpp \
    src/controller/lyricscontroller.cpp \
    src/controller/mainwindowcontroller.cpp \
    src/controller/musicplayercontroller.cpp \
    src/controller/playfunccontroller.cpp \
    src/model/downloadmodel.cpp \
    src/model/localmusicmodel.cpp \
    src/model/mainwindowmodel.cpp \
    src/model/music.cpp \
    src/model/musicplayermodel.cpp \
    src/model/playfuncmodel.cpp \
    src/view/choosedirsdialog.cpp \
    src/view/downloadview.cpp \
    src/view/localmusicview.cpp \
    src/view/mainwindow.cpp \
    src/view/musicplayerview.cpp \
    src/view/playfuncview.cpp \
    src/main.cpp \
    src/util/util.cpp


HEADERS += \
    src/controller/downloadcontroller.h \
    src/controller/localmusiccontroller.h \
    src/controller/lyricscontroller.h \
    src/controller/mainwindowcontroller.h \
    src/controller/musicplayercontroller.h \
    src/controller/playfunccontroller.h \
    src/model/downloadmodel.h \
    src/model/localmusicmodel.h \
    src/model/mainwindowmodel.h \
    src/model/music.h \
    src/model/musicplayermodel.h \
    src/model/playfuncmodel.h \
    src/view/choosedirsdialog.h \
    src/view/downloadview.h \
    src/view/localmusicview.h \
    src/view/mainwindow.h \
    src/view/musicplayerview.h \
    src/view/playfuncview.h \
    src/util/util.h

FORMS += \
    src/view/playfuncview.ui \
    src/view/musicplayerview.ui \
    src/view/mainwindow.ui \
    src/view/localmusicview.ui \
    src/view/downloadview.ui \
    src/view/choosedirsdialog.ui

DISTFILES += \
    src/document

RESOURCES += \
    resources/uiresources.qrc

INCLUDEPATH += $$PWD/src/
INCLUDEPATH += $$PWD/src/controller/
INCLUDEPATH += $$PWD/src/model/
INCLUDEPATH += $$PWD/src/view/
INCLUDEPATH += $$PWD/src/util/

