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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    createActions();
    createMenues();
    createToolBars();
    createCentralWidget();
    createStatusBar();
}

void MainWindow::createCentralWidget()
{
    Plotter *pl = new Plotter(this);

    QVector<QPointF> data(200);
    for (int var = 0; var < data.count(); ++var) {
        data[var] = QPointF(var, var / 2 ) ;
    }

    pl->setCurveData(1,data);

    QTableWidget *table = new QTableWidget(this);
    table->setColumnCount(1);
    table->setColumnWidth(0, 200);
    table->setRowCount(2000);
    table->verticalHeader()->setMaximumWidth(36);

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
    toolb->addAction(closeAction);
    toolb->addAction(saveFileAction);
}

void MainWindow::createStatusBar()
{
    this->statusBar()->show();
}
