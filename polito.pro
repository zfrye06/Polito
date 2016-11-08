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
    src/painthandler.cpp \
    src/layermenu.cpp \
    src/scrubber.cpp \
    src/previewarea.cpp \
    src/animation.cpp \
    src/frame.cpp \
    src/layer.cpp \
    src/toolbar.cpp \
<<<<<<< HEAD
    src/keybindingdialog.cpp \
    src/twitterdialog.cpp \
    src/fpsdialog.cpp
=======
    src/keybindingdialog.cpp
>>>>>>> 88f0f099ae299fdea03b281ef858825fa302f026

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
<<<<<<< HEAD
    src/animationwidgets.h \
    src/keybindingdialog.h \
    src/twitterdialog.h \
    src/fpsdialog.h

FORMS    += src/mainwindow.ui \
    src/imagesizedialog.ui \
    src/keybindingdialog.ui \
    src/twitterdialog.ui \
    src/fpsdialog.ui
=======
    src/keybindingdialog.h

FORMS    += src/mainwindow.ui \
    src/imagesizedialog.ui \
    src/keybindingdialog.ui
>>>>>>> 88f0f099ae299fdea03b281ef858825fa302f026

RESOURCES += \
    icons.qrc
