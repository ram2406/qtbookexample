#include <QtGui/QApplication>
#include "mainwindow.h"

#include "gotocelldialog/gotocelldialog.h"
#include "fdialog/finddialog.h"
#include "sortdialog/sortdialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}


//25.07.2012
//03.03.2013
//
