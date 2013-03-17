#include <QApplication>
#include "mainwindow.h"
#include "hexspinbox.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    //HexSpinBox *h = new HexSpinBox(0);
    //h->show();
    //w.setCentralWidget(h);
    //w.sizeHint();

    w.show();

    return a.exec();
    //03/16/13
}

