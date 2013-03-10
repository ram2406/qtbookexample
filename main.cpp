#include <QtGui/QApplication>
#include "mainwindow.h"

#include "gotocelldialog/gotocelldialog.h"
#include "fdialog/finddialog.h"
#include "sortdialog/sortdialog.h"

#include <QSplashScreen>

void loadModules() {
    //int test = 0;     for(int i = 0; i <1000000000; i++) test= (i+1) / 2;
}
void establishConnections() {
    //for(int i = 0; i <10000000; i++);
}

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    QSplashScreen *splash = new QSplashScreen;


    splash->setPixmap(QPixmap((QObject::tr(":/Resource/excel256.png"))));
    splash->show();

    Qt::Alignment bottomCenter = Qt::AlignBottom | Qt::AlignCenter;

    splash->showMessage(QObject::tr("Setting up the main window..."),
    bottomCenter, Qt::white);

    MainWindow mainWin;
    splash->showMessage(QObject::tr("Loading modules..."),
    bottomCenter, Qt::white);
    loadModules();
    splash->showMessage(QObject::tr("Establishing connections..."),
    bottomCenter, Qt::white);
    establishConnections();
    mainWin.show();
    splash->finish(&mainWin);
    delete splash;
    return app.exec();
    /*
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
    */
}


//25.07.2012
//03.03.2013
//03/10/13
