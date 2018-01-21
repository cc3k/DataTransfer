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
    filesystemwidget.cpp \
    configxmlreader.cpp \
    filesystementry.cpp \
    copyfile.cpp \
    filesystemdirread.cpp \
    filesystemdirreaddialog.cpp \
    filesystemdeletedialog.cpp \
    filesystemdircreatedialog.cpp

HEADERS  += mainwindow.h \
    customtableview.h \
    customdirmodel.h \
    filesystemwidget.h \
    configxmlreader.h \
    filesystementry.h \
    copyfile.h \
    filesystemdirreaddialog.h \
    filesystemdirread.h \
    filesystemdeletedialog.h \
    filesystemdircreatedialog.h

FORMS    += mainwindow.ui \
    filesystemwidget.ui \
    filesystemdirreaddialog.ui \
    filesystemdeletedialog.ui \
    filesystemdircreatedialog.ui

RESOURCES += \
    resources.qrc
