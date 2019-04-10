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
    src/controller/localmusiccontroller.cpp \
    src/controller/lyricscontroller.cpp \
    src/controller/mainwindowcontroller.cpp \
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
    src/view/playfuncview.cpp \
    src/main.cpp \
    src/util/util.cpp \
    src/controller/musicplayercontroller.cpp \
    src/controller/downloadcontroller.cpp \
    src/model/musicsheet.cpp \
    src/view/playsheetview.cpp \
    src/view/musicplayerview.cpp \
    src/view/musiclistitemview.cpp \
    src/view/searchview.cpp \
    src/model/playsheetmodel.cpp \
    src/controller/playsheetcontroller.cpp \
    src/globalvariable.cpp \
    src/globalconstant.cpp \
    src/view/playmusicdetialview.cpp \
    src/controller/playmusicdetialcontroller.cpp \
    src/model/playmusicdetialmodel.cpp \
    src/model/user.cpp


HEADERS += \
    src/controller/localmusiccontroller.h \
    src/controller/lyricscontroller.h \
    src/controller/mainwindowcontroller.h \
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
    src/util/util.h \
    src/controller/musicplayercontroller.h \
    src/controller/downloadcontroller.h \
    src/model/musicsheet.h \
    src/view/playsheetview.h \
    src/view/musiclistitemview.h \
    src/view/searchview.h \
    src/model/playsheetmodel.h \
    src/controller/playsheetcontroller.h \
    src/globalvariable.h \
    src/globalconstant.h \
    src/view/playmusicdetialview.h \
    src/controller/playmusicdetialcontroller.h \
    src/model/playmusicdetialmodel.h \
    src/model/user.h

FORMS += \
    src/view/playfuncview.ui \
    src/view/musicplayerview.ui \
    src/view/mainwindow.ui \
    src/view/localmusicview.ui \
    src/view/downloadview.ui \
    src/view/choosedirsdialog.ui \
    src/view/playsheetview.ui \
    src/view/musiclistitemview.ui \
    src/view/searchview.ui \
    src/view/playmusicdetialview.ui

DISTFILES += \
    src/document

RESOURCES += \
    resources/uiresources.qrc

INCLUDEPATH += $$PWD/src/
INCLUDEPATH += $$PWD/src/controller/
INCLUDEPATH += $$PWD/src/model/
INCLUDEPATH += $$PWD/src/view/
INCLUDEPATH += $$PWD/src/util/
INCLUDEPATH += -I D:/Anaconda3/include/

LIBS += -LD:/Anaconda3/libs -lpython37

