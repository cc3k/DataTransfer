#-------------------------------------------------
#
# Project created by QtCreator 2017-12-20T12:35:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataTransfer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fileexplorermodelwidget.cpp

HEADERS  += mainwindow.h \
    fileexplorer.h \
    fileexplorermodelwidget.h

FORMS    += mainwindow.ui \
    fileexplorermodelwidget.ui
