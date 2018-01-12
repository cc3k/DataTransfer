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
    fileexplorermodelwidget.cpp \
    customtableview.cpp \
    customdirmodel.cpp

HEADERS  += mainwindow.h \
    fileexplorermodelwidget.h \
    customtableview.h \
    customdirmodel.h

FORMS    += mainwindow.ui \
    fileexplorermodelwidget.ui
