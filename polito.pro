#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T15:51:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = polito
TEMPLATE = app

include(o2/src/src.pri)

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/action.cpp \
    src/imagesizedialog.cpp \
    src/drawarea.cpp \
    src/painthandler.cpp \
    src/layermenu.cpp \
    src/scrubber.cpp \
    src/previewarea.cpp \
    src/animation.cpp \
    src/frame.cpp \
    src/layer.cpp \
    src/toolbar.cpp \
    src/keybindingdialog.cpp \
    src/twitterdialog.cpp

HEADERS  += src/mainwindow.h \
    src/action.h \
    src/imagesizedialog.h \
    src/drawarea.h \
    src/painthandler.h \
    src/layermenu.h \
    src/scrubber.h \
    src/previewarea.h \
    src/animation.h \
    src/frame.h \
    src/layer.h \
    src/animationeventemitter.h \
    src/toolbar.h \
    src/animationwidgets.h \
    src/keybindingdialog.h \
    src/twitterdialog.h

FORMS    += src/mainwindow.ui \
    src/imagesizedialog.ui \
    src/keybindingdialog.ui \
    src/twitterdialog.ui

RESOURCES += \
    icons.qrc

INCLUDEPATH += $$PWD/gif-h

DISTFILES +=
