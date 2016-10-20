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
    src/frame.cpp \
    src/toolbar.cpp \
    src/layermenu.cpp \
    src/scrubber.cpp \
    src/previewarea.cpp

HEADERS  += src/mainwindow.h \
    src/action.h \
    src/imagesizedialog.h \
    src/drawarea.h \
    src/frame.h \
    src/toolbar.h \
    src/layermenu.h \
    src/scrubber.h \
    src/previewarea.h

FORMS    += src/mainwindow.ui \
    src/imagesizedialog.ui
