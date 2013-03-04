#-------------------------------------------------
#
# Project created by QtCreator 2012-07-24T09:32:24
#
#-------------------------------------------------

QT       += core gui

TARGET = QtBookExample
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fdialog/finddialog.cpp \
    sortdialog/sortdialog.cpp \
    gotocelldialog/gotocelldialog.cpp \
    spreadsheet.cpp

HEADERS  += mainwindow.h \
    fdialog/finddialog.h \
    gotocelldialog/ui_gotocelldialog.h \
    sortdialog/ui_sortdialog.h \
    sortdialog/sortdialog.h \
    gotocelldialog/gotocelldialog.h \
    spreadsheet.h

FORMS    += mainwindow.ui \
    sortdialog.ui \
    gotocelldialog.ui

RESOURCES += \
    spreadsheet.qrc

OTHER_FILES += \
    Resource/excel.png
