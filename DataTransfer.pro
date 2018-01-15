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
    customtableview.cpp \
    customdirmodel.cpp \
    filesystemmountpoint.cpp \
    filesystemwidget.cpp \

HEADERS  += mainwindow.h \
    customtableview.h \
    customdirmodel.h \
    filesystemmountpoint.h \
    filesystemwidget.h \

FORMS    += mainwindow.ui \
    filesystemwidget.ui
