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

void graph() {


    QMainWindow win;





    Plotter *p = new Plotter(&win);
    for(int i = 0; i < 6; i++) {
        QVector<QPointF> data(20);
        int x = rand() , y = rand();
        for (int var = 0; var < data.size(); ++var) {
            data[var].setX(x * var);
            data[var].setY(y * var);
        }
        p->setCurveData(i , data);

    }




    win.setCentralWidget(p);

    win.show();


}

void mainWindow() {
    setlocale(LC_CTYPE, "1251");

    MainWindow *w = new MainWindow;
    w->show();
}

int findFileDialog() {

    FindFileDialog fd;


    return fd.exec();
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

