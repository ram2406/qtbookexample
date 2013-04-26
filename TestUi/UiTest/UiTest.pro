#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T16:21:25
#
#-------------------------------------------------

QT       += core gui

TARGET = ModelPostproc
TEMPLATE = app
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += main.cpp\
    plotter.cpp \
    DEMP/Dempher.cpp \
    examples/iconeditor.cpp \
    examples/hexspinbox.cpp \
    examples/findfiledialog.cpp \
    mainwindow.cpp \
    openfilefordemp.cpp \
    inter/INTERPOL.CPP


HEADERS  += \
    plotter.h \
    DEMP/dempher.h \
    examples/iconeditor.h \
    examples/hexspinbox.h \
    examples/findfiledialog.h \
    mainwindow.h \
    openfilefordemp.h \
    inter/INTERPOL.h \
    ProgSettings.h

FORMS    +=

RESOURCES += \
    plotter.qrc \
    main.qrc
