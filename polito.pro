#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T15:51:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = polito
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/action.cpp \
    src/imagesizedialog.cpp \
    src/drawarea.cpp \
    src/layermenu.cpp \
    src/scrubber.cpp \
    src/previewarea.cpp \
    src/animation.cpp \
    src/toolbar.cpp

HEADERS  += src/mainwindow.h \
    src/action.h \
    src/imagesizedialog.h \
    src/drawarea.h \
    src/layermenu.h \
    src/scrubber.h \
    src/previewarea.h \
    src/animation.h \
    src/toolbar.h

FORMS    += src/mainwindow.ui \
    src/imagesizedialog.ui
