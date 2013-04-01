#include <QApplication>
#include "mainwindow.h"
#include "hexspinbox.h"
#include "plotter.h"
#include <QMenuBar>
#include <QToolBar>





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow win;





    Plotter *p = new Plotter(&win);
    for(int i = 0; i < 6; i++) {
        QVector<QPointF> data(20);
        int x = random() , y = random();
        for (int var = 0; var < data.size(); ++var) {
            data[var].setX(x * var);
            data[var].setY(y * var);
        }
        p->setCurveData(i , data);

    }




    win.setCentralWidget(p);
    //HexSpinBox *h = new HexSpinBox(0);
    //h->show();
    //w.setCentralWidget(h);
    //w.sizeHint();

    win.show();

    return a.exec();
    //03/16/13
    //03/17/13 page 122
}

