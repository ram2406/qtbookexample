#include <QtGui/QApplication>
#include "mainwindow.h"

#include "gotocelldialog/gotocelldialog.h"
#include "fdialog/finddialog.h"
#include "sortdialog/sortdialog.h"

#include <QSplashScreen>
#include <QWaitCondition>
#include <QMutex>

static void msleep(unsigned long msecs)
    {
        QMutex mutex;
        mutex.lock();

        QWaitCondition waitCondition;
        waitCondition.wait(&mutex, msecs);

        mutex.unlock();
    }


void loadModules() {
    msleep(1000);
}
void establishConnections() {
    msleep(1000);
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
    bottomCenter, Qt::black);
    loadModules();
    splash->showMessage(QObject::tr("Establishing connections..."),
    bottomCenter, Qt::black);
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
