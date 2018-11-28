#-------------------------------------------------
#
# Project created by QtCreator 2018-11-28T14:58:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtCustomControllers
TEMPLATE = app

CONFIG += debug_and_release
CONFIG(debug, debug|release){
    DESTDIR = $$PWD/bin/debug
} else {
    DESTDIR = $$PWD/bin/release
}

SOURCES += main.cpp\
        MainWindow.cpp \
    QtCustomToastWidget.cpp \
    CustomShadowEffect.cpp

HEADERS  += MainWindow.h \
    QtCustomToastWidget.h \
    CustomShadowEffect.h

FORMS    += MainWindow.ui
