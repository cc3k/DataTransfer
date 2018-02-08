#-------------------------------------------------
#
# Project created by QtCreator 2017-12-20T12:35:07
#
#-------------------------------------------------

QT       += network core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataTransfer
TEMPLATE = app

QMAKE_CXXFLAGS += -std=gnu++11

SOURCES += main.cpp\
        mainwindow.cpp \
    filesystem/configreader.cpp \
    filesystem/filesystementry.cpp \
    filesystem/filesystemmodel.cpp \
    filesystem/focuscontroldelegate.cpp \
    filesystem/panelwidget.cpp \
    filesystem/tableview.cpp \
    filesystem/operationcalculator.cpp \
    filesystem/operationcalculatorwidget.cpp \
    filesystem/operationcopywidget.cpp \
    filesystem/operationcopy.cpp \
    filesystem/operationcopydialogwidget.cpp

HEADERS  += mainwindow.h \
    filesystem/configreader.h \
    filesystem/filesystementry.h \
    filesystem/filesystemmodel.h \
    filesystem/focuscontroldelegate.h \
    filesystem/panelwidget.h \
    filesystem/tableview.h \
    filesystem/operationcalculator.h \
    filesystem/operationcalculatorwidget.h \
    filesystem/operationcopywidget.h \
    filesystem/operationcopy.h \
    filesystem/operationcopydialogwidget.h

FORMS    += mainwindow.ui \
    filesystem/panelwidget.ui \
    filesystem/operationcopydialogwidget.ui

RESOURCES += \
    resource.qrc
