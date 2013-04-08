#include "mainwindow.h"
#include <QTableWidget>
#include "plotter.h"
#include <QMenuBar>
#include <QToolBar>
#include <QSplitter>
#include <QStatusBar>
#include <QList>
#include <QHeaderView>
#include <cmath>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowTitle(tr("Программа демпфирования"));
    this->setWindowIcon(QIcon(tr(":/images/main.PNG")));
    createActions();
    //createMenues();
    createToolBars();
    createCentralWidget();
    createStatusBar();

}

void MainWindow::createCentralWidget()
{
    Plotter *pl = new Plotter(this);

    QVector<QPointF> data(2000);
    for (int var = 0; var < data.count(); ++var) {
        data[var] = QPointF(var, var / 2 ) ;
    }

    pl->setCurveData(1,data);

    //QVector<QPointF> data(200);
    for (int var = 0; var < data.count(); ++var) {
        data[var] = QPointF(var ,std::sin(var*rand())+ 10  ) ;
    }

    pl->setCurveData(2,data);


    QTableWidget *table = new QTableWidget(this);
    table->setColumnCount(1);
    table->setRowCount(2000);
    table->verticalHeader()->setMaximumWidth(36);
    table->horizontalHeader()->setStretchLastSection(true);

    for (int var = 0; var < data.count(); ++var) {
        QTableWidgetItem *item = new QTableWidgetItem;

        QString str;
        str += QString::number( data[var].x() ) + " " + QString::number( data[var].y() );

        item->setText(str);
        table->setItem(var , 0 ,item);
    }

    QTableWidgetItem *header = new QTableWidgetItem;
    header->setTextAlignment(Qt::AlignLeft);
    header->setText(tr("Кадры"));
    table->setHorizontalHeaderItem(0, header);

    QSplitter *s = new QSplitter(Qt::Horizontal);
    s->addWidget(table);
    s->addWidget(pl);
    QList<int> sizes;
    sizes.append(125);
    sizes.append(475);

    s->setSizes(sizes);

    this->setCentralWidget(s);


}

void MainWindow::createActions()
{
    openFileAction = new QAction(tr("&Открыть"), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(tr("Открыть файл содержащий сигналы управляющей программы"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));

    saveFileAction = new QAction(tr("&Сохранить"), this);
    saveFileAction->setShortcut(tr("Ctrl+S"));
    saveFileAction->setStatusTip(tr("Сохранить в файл управляющих сигналов после демп"));

    closeAction = new QAction(tr("&Закрыть"), this);
    closeAction->setShortcut(tr("Ctrl+Q"));
    closeAction->setStatusTip(tr("Закрыть приложение"));
}


void MainWindow::createMenues()
{
    QMenu *fileMenu = this->menuBar()->addMenu(tr("&Файл"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(closeAction);
    fileMenu->addAction(saveFileAction);
}

void MainWindow::createToolBars()
{
    QToolBar *toolb = this->addToolBar(tr("&Файл"));
    toolb->addAction(openFileAction);

    toolb->addAction(saveFileAction);

    toolb->addAction(closeAction);
}

void MainWindow::createStatusBar()
{
    this->statusBar()->show();
}

#include <cstdio>
#include "DEMP/dempher.h"
#include "openfilefordemp.h"

void MainWindow::openFile()
{

    OpenFileForDemp o(this);
    o.exec();

    /*QFileDialog dlg;
    dlg.show();*/
    /*DempherClass dc;

    CONFIG conf= {1000 , 2000};

    result_code res = dc.exec("C:\\data\\gcode\\10777007.PL1" , "C:\\data\\gcode\\10777007.PL2", false, conf);

    if(res != SUCCESS) {
        QMessageBox::warning(this , tr("Ошибка"), tr( getTextResCode(res).c_str() ), QMessageBox::Ok , QMessageBox::Cancel);
    }
    */
}

void MainWindow::saveFile()
{
}
