#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T16:21:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UiTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    hexspinbox.cpp \
    iconeditor.cpp \
    plotter.cpp \
    DEMP/Dempher.cpp

HEADERS  += mainwindow.h \
    hexspinbox.h \
    iconeditor.h \
    plotter.h \
    DEMP/dempher.h

FORMS    += mainwindow.ui

RESOURCES += \
    plotter.qrc
