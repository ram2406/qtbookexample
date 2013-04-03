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
    plotter.cpp \
    DEMP/Dempher.cpp \
    examples/iconeditor.cpp \
    examples/hexspinbox.cpp \
    examples/findfiledialog.cpp \
    mainwindow.cpp

HEADERS  += \
    hexspinbox.h \
    plotter.h \
    DEMP/dempher.h \
    examples/iconeditor.h \
    examples/hexspinbox.h \
    examples/findfiledialog.h \
    mainwindow.h

FORMS    +=

RESOURCES += \
    plotter.qrc
