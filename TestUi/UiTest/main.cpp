#include <QApplication>
#include "mainwindow.h"
#include <clocale>
#include "plotter.h"
#include <QMenuBar>
#include <QToolBar>
#include "examples/findfiledialog.h"
#include <QTextCodec>

#include <stdio.h>

#include <QDebug>

void fun_output(std::string formatText , ...) {
    printf(formatText.c_str());
    qDebug(formatText.c_str()) ;
}


void mainWindow() {
    setlocale(LC_CTYPE, "1251");

    MainWindow *w = new MainWindow;
    w->show();
}



int main(int argc, char *argv[])
{

    fun_output("\n\nTEST\n");

    QApplication a(argc, argv);
    QTextCodec::setCodecForTr( QTextCodec::codecForName( "Utf8" ) );
    //return findFileDialog();
    mainWindow();
    return a.exec();
}

