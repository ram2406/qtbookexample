#include <QApplication>
#include "mainwindow.h"

#include "plotter.h"
#include <QMenuBar>
#include <QToolBar>
#include "examples/findfiledialog.h"


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
    MainWindow *w = new MainWindow;
    w->show();
}

int findFileDialog() {

    FindFileDialog fd;


    return fd.exec();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //return findFileDialog();
    mainWindow();
    return a.exec();
}

