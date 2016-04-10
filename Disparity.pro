#-------------------------------------------------
#
# Project created by QtCreator 2016-02-13T17:25:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Disparity
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    disparitymap.cpp \
    grayscale.cpp

HEADERS  += mainwindow.h \
    disparitymap.h \
    grayscale.h

FORMS    += mainwindow.ui
