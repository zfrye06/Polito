#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T15:51:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = polito
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    action.cpp \
    imagesizedialog.cpp \
    drawarea.cpp \
    frame.cpp \
    toolbar.cpp \
    layermenu.cpp \
    scrubber.cpp \
    previewarea.cpp

HEADERS  += mainwindow.h \
    action.h \
    imagesizedialog.h \
    drawarea.h \
    frame.h \
    toolbar.h \
    layermenu.h \
    scrubber.h \
    previewarea.h

FORMS    += mainwindow.ui \
    imagesizedialog.ui
