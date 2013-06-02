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
#include <QLocale>
#include <QTextCodec>
#include <QTextStream>
#include <QDockWidget>
#include "inter/INTERPOL.h"
#include <algorithm>
#include <fstream>
#include <QCheckBox>
#include <QDebug>

#include "ProgSettings.h"

#include <string>

#include <cstdio>
#include "DEMP/dempher.h"
#include "openfilefordemp.h"

#include <QSettings>
#include <QMdiArea>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), showX(false), showY (false), showZ (false), showNode(false)
{
    this->setWindowTitle(  tr("Программа демпфирования") );
    this->setWindowIcon(QIcon(tr(":/images/main.PNG")));

    plDemp = new Plotter(this);
    plInterpol = new Plotter(this);
    plTopView = new Plotter(this);
    plSideView = new Plotter(this);



    createActions();
    //createMenues();
    createToolBars();
    createCentralWidget();
    createStatusBar();
    loadSettings();







}

void MainWindow::loadCLDATA()
{
    QFile inputFile( QString::fromStdWString(this->settings.clDataFileName));

    int rowNum = 0;
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while ( !in.atEnd() )
       {
          QString line = in.readLine();
          QTableWidgetItem *item = new QTableWidgetItem;

          item->setText(line);
          table->setItem(rowNum++ , 0 ,item);

       }
    }
    inputFile.close();

}

void MainWindow::interpolExec()
{
    interpol(settings.clDataFileName, settings.interFileName);
}

void MainWindow::loadGraph()
{
    loadGraphInterpol(this->settings.interFileName, plInterpol);
    loadGraphDemp(this->settings.dempFileName, plDemp);
    loadGraphTopView(this->settings.dempFileName, plTopView);
    loadGraphSideView(this->settings.dempFileName, plSideView);
}

void MainWindow::help()
{
    QMessageBox::about(this, tr("Описание программы"),tr("<h3>Программа подготовки декодированных управляющих программ для оборудования с ЧПУ</h3>"
                                                         "<p>Программа предназначена "
                                                         "для моделирование обработки управляющей программы поспроцессором "
                                                         "и демонстрации концепции демпфирования во время воспроизведения станком с ЧПУ") );
}

void MainWindow::setDrawNode(bool value)    {
    this->showNode  =   value;
    plDemp->setDrawNode(value);
    plInterpol->setDrawNode(value);
    plTopView->setDrawNode(value);
    plSideView->setDrawNode(value);

}
void MainWindow::setShowNodeX(bool value)   {
    this->showX     =   value;
    plDemp->setVisibleCurve(0, value);
    plInterpol->setVisibleCurve(0, value);
    plTopView->setVisibleCurve(0, value);
    plSideView->setVisibleCurve(0, value);
}
void MainWindow::setShowNodeY(bool value)   {
    this->showY     =   value;
    plDemp->setVisibleCurve(1, value);
    plInterpol->setVisibleCurve(1, value);
    plTopView->setVisibleCurve(1, value);
    plSideView->setVisibleCurve(1, value);
}
void MainWindow::setShowNodeZ(bool value)   {
    this->showZ     =   value;
    plDemp->setVisibleCurve(2, value);
    plInterpol->setVisibleCurve(2, value);
    plTopView->setVisibleCurve(2, value);
    plSideView->setVisibleCurve(2, value);
}

void MainWindow::exec()
{
    if( !this->settings.validate() )  {
        this->statusBar()->showMessage(tr("Внесите настройки приложения, нажав 'Настройки'"), 3000);
        return;
    }
    try {
        this->loadCLDATA();
        this->interpolExec();

        DempherClass dc;
        CONFIG conf= {settings.df1 , settings.df2};
        qDebug() << tr("Обработка демпфирования. Конфигурация df1 = %1 , df2 = %2").arg(settings.df1, settings.df2);
        result_code res = dc.exec(settings.interFileName , settings.dempFileName, false, conf);

        if(res != SUCCESS) {
            QMessageBox::warning(this , tr("Ошибка"), tr( getTextResCode(res).c_str() ), QMessageBox::Ok );
        }
        loadGraph();
    }
    catch(const char* s) {
        QMessageBox::warning(this , tr("Ошибка"), tr( s ), QMessageBox::Ok );
    }
    catch(const wchar_t* s) {
        QMessageBox::warning(this , tr("Ошибка"),  QString::fromWCharArray( s ), QMessageBox::Ok );
    }
    catch(...) {
        QMessageBox::warning(this , tr("Ошибка"), tr( "Произошла неизвестная ошибка" ), QMessageBox::Ok );
    }


}

void MainWindow::createCentralWidget()
{


    /*
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
    */

    table = new QTableWidget(this);
    table->setColumnCount(1);

    table->verticalHeader()->setMaximumWidth(36);

    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setVisible(false);
    table->setRowCount(2000);
    /*
    for (int var = 0; var < data.count(); ++var) {
        QTableWidgetItem *item = new QTableWidgetItem;

        QString str;
        str += QString::number( data[var].x() ) + " " + QString::number( data[var].y() );

        item->setText(str);
        table->setItem(var , 0 ,item);
    }//*/

    QTableWidgetItem *header = new QTableWidgetItem;
    header->setTextAlignment(Qt::AlignLeft);
    header->setText(tr("Кадры"));
    table->setHorizontalHeaderItem(0, header);

    {
    QDockWidget *dc1 = new QDockWidget(tr("Программа"));
    dc1->setObjectName(tr("progDock"));
    dc1->setWidget(table);
    dc1->setAllowedAreas(Qt::AllDockWidgetAreas);
    this->addDockWidget(Qt::LeftDockWidgetArea,dc1);

    }
    {//demp
        QDockWidget *dc2 = new QDockWidget(tr("График после демпфирования"));
        dc2->setObjectName(tr("plDempDock"));
        plDemp->setTitle(tr("График после демпфирования"));
        plDemp->setAxisName( tr("Скорось подачи импульсов"), tr("Ось смещения по Х,Y,Z"));
        dc2->setWidget(plDemp);
        dc2->setAllowedAreas(Qt::AllDockWidgetAreas);

        this->addDockWidget(Qt::RightDockWidgetArea,dc2);

    }
    {//interpol
        QDockWidget *dc2 = new QDockWidget(tr("График без демпфирования"));
        dc2->setObjectName(tr("plInterpolDock"));
        dc2->setWidget(plInterpol);
        plInterpol->setTitle(tr("График без демпфирования"));
        plInterpol->setAxisName( tr("Скорось подачи импульсов"), tr("Ось смещения по Х,Y,Z"));
        dc2->setAllowedAreas(Qt::AllDockWidgetAreas);

        this->addDockWidget(Qt::RightDockWidgetArea,dc2);

    }
    {//top view
        QDockWidget *dc2 = new QDockWidget(tr("График - вид сверху"));
        dc2->setObjectName(tr("plTopViewDock"));
        dc2->setWidget(plTopView);
        plTopView->setAxisName( tr("Ось смещения по Х"), tr("Ось смещения по Y"));
        plTopView->setTitle(tr("График - вид сверху"));
        dc2->setAllowedAreas(Qt::AllDockWidgetAreas);

        this->addDockWidget(Qt::RightDockWidgetArea,dc2);

    }
    {//side view
        QDockWidget *dc2 = new QDockWidget(tr("График - вид сбоку"));
        dc2->setObjectName(tr("plSideViewDock"));
        dc2->setWidget(plSideView);
        dc2->setAllowedAreas(Qt::AllDockWidgetAreas);
        plSideView->setAxisName( tr("Ось смещения по Х"), tr("Ось смещения по Z"));
        plSideView->setTitle(tr("График - вид сбоку"));
        this->addDockWidget(Qt::RightDockWidgetArea,dc2);

    }


}

void MainWindow::loadGraphDemp(std::wstring dempFileName, Plotter *pl)
{
    qDebug()<< tr("Строим графитк после демпфирования , файл : %1").arg(QString::fromStdWString(dempFileName));
    FILE* dempf =_wfopen(dempFileName.c_str(), L"rb");
    if(!dempf) throw L"Не удалось открыть файл";
    int byte ;



    QVector<QPointF> dataX(2000);
    QVector<QPointF> dataY(2000);
    QVector<QPointF> dataZ(2000);

    unsigned int curPos = 0;

    int maxY = 0, minY = 0;

    int X = 0, Y = 0 , Z = 0;

    dataX.append(QPointF( curPos , X));
    dataY.append(QPointF( curPos , Y));
    dataZ.append(QPointF( curPos , Z));

    while ( (byte = fgetc(dempf)) != EOF ) {

        if(byte == 15 )
            continue;

        if(byte & 1)
            X++;
        if(byte & 2)
            X--;

        if(byte & 1 || byte & 2)
            dataX.append(QPointF(curPos , X));

        if(byte & 4)
            Y++;
        if(byte & 8)
            Y--;

        if(byte & 4 || byte & 8)
            dataY.append(QPointF(curPos , Y));

        if(byte & 16)
            Z++;
        if(byte & 32)
            Z--;

        if(byte & 16 || byte & 32)
            dataZ.append(QPointF(curPos , Z));

        maxY = std::max(maxY, X);
        maxY = std::max(maxY, Y);
        maxY = std::max(maxY, Z);

        minY = std::min(minY, X);
        minY = std::min(minY, Y);
        minY = std::min(minY, Z);

        curPos++;
    }
    PlotSettings set;
    set.maxX = curPos;
    set.maxY = maxY;
    set.minX = 0;
    set.minY = minY;

    pl->setPlotSettings(set);
    pl->setCurveData(0,dataX);
    pl->setCurveData(1,dataY);
    pl->setCurveData(2,dataZ);
    fclose(dempf);
}

void MainWindow::loadGraphInterpol(std::wstring interpolFileName, Plotter *pl)
{
    qDebug()<< tr("Строим графитк после интерполяции , файл : %1").arg(QString::fromStdWString(interpolFileName));
    FILE* dempf =_wfopen(interpolFileName.c_str(), L"rb");
    if(!dempf) throw L"Не удалось открыть файл";
    int byte ;



    QVector<QPointF> dataX(2000);
    QVector<QPointF> dataY(2000);
    QVector<QPointF> dataZ(2000);

    unsigned int curPos = 0;

    int maxY = 0, minY =0;

    int X = 0, Y = 0 , Z = 0;

    dataX.append(QPointF( curPos , X));
    dataY.append(QPointF( curPos , Y));
    dataZ.append(QPointF( curPos , Z));

    while ( (byte = fgetc(dempf)) != EOF ) {

        if(byte == 15)
            continue;

        if(byte & 1)
            X++;
        if(byte & 2)
            X--;

        if(byte & 1 || byte & 2)
            dataX.append(QPointF(curPos , X));

        if(byte & 4)
            Y++;
        if(byte & 8)
            Y--;

        if(byte & 4 || byte & 8)
            dataY.append(QPointF(curPos , Y));

        if(byte & 16)
            Z++;
        if(byte & 32)
            Z--;

        if(byte & 16 || byte & 32)
            dataZ.append(QPointF(curPos , Z));

        maxY = std::max(maxY, X);
        maxY = std::max(maxY, Y);
        maxY = std::max(maxY, Z);

        minY = std::min(minY, X);
        minY = std::min(minY, Y);
        minY = std::min(minY, Z);

        curPos++;
    }
    PlotSettings set;
    set.maxX = curPos;
    set.maxY = maxY;
    set.minX = 0;
    set.minY = minY;

    pl->setPlotSettings(set);
    pl->setCurveData(0,dataX);
    pl->setCurveData(1,dataY);
    pl->setCurveData(2,dataZ);
    fclose(dempf);
}

void MainWindow::loadGraphTopView(std::wstring dempFileName, Plotter *pl)
{
    qDebug()<< tr("Строим графитк после интерполяции , файл : %1").arg(QString::fromStdWString(dempFileName));
    FILE* dempf =_wfopen(dempFileName.c_str(), L"rb");
    if(!dempf) throw L"Не удалось открыть файл";
    int byte ;



    QVector<QPointF> dataX(2000);

    int maxY = 0, maxX = 0, minY = 0, minX =0;

    int X = 0, Y = 0;

    dataX.append(QPointF( X , Y));

    while ( (byte = fgetc(dempf)) != EOF ) {

        //qDebug()<< tr("Байт : %1").arg(byte);
        if(!byte || byte == 15)
            continue;

        if(byte & 1)  X++;
        if(byte & 2)  X--;

        if(byte & 4)  Y++;
        if(byte & 8)  Y--;


        maxX = std::max(maxX, X);
        maxY = std::max(maxY, Y);

        minX = std::min(minX, X);
        minY = std::min(minY, Y);


        dataX.append(QPointF(X , Y));


    }
    PlotSettings set;
    set.maxX = maxX;
    set.maxY = maxY;
    set.minX = minX;
    set.minY = minY;

    pl->setPlotSettings(set);
    pl->setCurveData(0,dataX);
    fclose(dempf);
}

void MainWindow::loadGraphSideView(std::wstring dempFileName, Plotter *pl)
{
    qDebug()<< tr("Строим графитк после интерполяции , файл : %1").arg(QString::fromStdWString(dempFileName));
    FILE* dempf =_wfopen(dempFileName.c_str(), L"rb");
    if(!dempf) throw L"Не удалось открыть файл";
    int byte ;



    QVector<QPointF> dataX(2000);

    int maxZ = 0, maxX = 0, minX = 0, minZ = 0;

    int X = 0, Z = 0;

    dataX.append(QPointF( X , Z));

    while ( (byte = fgetc(dempf)) != EOF ) {

        //qDebug()<< tr("Байт : %1").arg(byte);
        if(!byte || byte == 15)
            continue;

        if(byte & 1)  X++;
        if(byte & 2)  X--;

        if(byte & 16)  Z++;
        if(byte & 32)  Z--;


        maxX = std::max(maxX, X);
        maxZ = std::max(maxZ, Z);

        minX = std::min(minX, X);
        minZ = std::min(minZ, Z);

        dataX.append(QPointF(X , Z));


    }
    PlotSettings set;
    set.maxX = maxX;
    set.maxY = maxZ;
    set.minX = minX;
    set.minY = minZ;

    pl->setPlotSettings(set);
    pl->setCurveData(0,dataX);
    fclose(dempf);
}

void MainWindow::createActions()
{

    startAction = new QAction(tr("Выполнить"), this);
    startAction->setShortcut(tr("Ctrl+R"));
    startAction->setStatusTip(tr("Выполнить интерполяцию, обработку алгоритмом демпфирования и построить график движения фрезы"));
    startAction->setIcon(QIcon(tr(":/images/start.png")));
    connect(startAction , SIGNAL(triggered()),  this , SLOT(exec()));

    startAction->setEnabled(false);

    settingsAction = new QAction(tr("&Настройки"), this);
    settingsAction->setShortcut(tr("Ctrl+O"));
    settingsAction->setStatusTip(tr("Изменить или задать настройки программы"));
    settingsAction->setIcon(QIcon(tr(":/images/settings.png")));
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(openFile()));

    closeAction = new QAction(tr("&Закрыть"), this);
    closeAction->setShortcut(tr("Ctrl+Q"));
    closeAction->setStatusTip(tr("Закрыть приложение"));
    connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

    helpAction = new QAction(tr("&Справка"), this);
    helpAction->setShortcut(tr("Ctrl+H"));
    helpAction->setStatusTip(tr("Информация о программе и краткое руководство пользователя"));
    helpAction->setIcon(QIcon(tr(":/images/help.png")));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(help()));

    drawNodeAction = new QAction(tr("Отображать &узлы"), this);
    drawNodeAction->setShortcut(tr("Ctrl+N"));
    drawNodeAction->setStatusTip(tr("Отображать узловые точки на графике"));
    drawNodeAction->setCheckable(true);
    drawNodeAction->setIcon(QIcon(tr(":/images/showNode.png")));
    connect(drawNodeAction, SIGNAL(toggled(bool)), this, SLOT(setDrawNode(bool)));
    drawNodeAction->setChecked(false);

    drawXAction = new QAction(tr("Отображать график движения по &X"), this);
    drawXAction->setShortcut(tr("Ctrl+X"));
    drawXAction->setStatusTip(tr("Отображать на графике движения фрезы по оси Х"));
    drawXAction->setCheckable(true);
    drawXAction->setIcon(QIcon(tr(":/images/showX.png")));
    connect(drawXAction, SIGNAL(toggled(bool)), this, SLOT(setShowNodeX(bool)));
    drawXAction->setChecked(true);

    drawYAction = new QAction(tr("Отображать график движения по &Y"), this);
    drawYAction->setShortcut(tr("Ctrl+Y"));
    drawYAction->setStatusTip(tr("Отображать на графике движения фрезы по оси Y"));
    drawYAction->setIcon(QIcon(tr(":/images/showY.png")));
    drawYAction->setCheckable(true);
    connect(drawYAction, SIGNAL(toggled(bool)), this, SLOT(setShowNodeY(bool)));
    drawYAction->setChecked(true);

    drawZAction = new QAction(tr("Отображать график движения по &Z"), this);
    drawZAction->setShortcut(tr("Ctrl+Z"));
    drawZAction->setStatusTip(tr("Отображать на графике движения фрезы по оси Z"));
    drawZAction->setIcon(QIcon(tr(":/images/showZ.png")));
    drawZAction->setCheckable(true);
    connect(drawZAction, SIGNAL(toggled(bool)), this, SLOT(setShowNodeZ(bool)));
    drawZAction->setChecked(true);

    fastModeAction = new QAction(tr("&Быстрая прорисовка"), this);
    fastModeAction->setShortcut(tr("Ctrl+F"));
    fastModeAction->setStatusTip(tr("Включить/выключить упрощенную прорисовку кривых путем отсечения точек"));
    fastModeAction->setCheckable(true);
    fastModeAction->setIcon(QIcon(tr(":/images/fastmode.png")));
    connect(fastModeAction, SIGNAL(toggled(bool)), plDemp, SLOT(setFastMode(bool)));
    fastModeAction->setChecked(true);
}


void MainWindow::createMenues()
{
    QMenu *fileMenu = this->menuBar()->addMenu(tr("&Файл"));
    fileMenu->addAction(settingsAction);
    fileMenu->addAction(closeAction);
    fileMenu->addAction(helpAction);

}

void MainWindow::createToolBars()
{
    mainToolBar = this->addToolBar(tr("&Файл"));
    mainToolBar->addAction(settingsAction);
    mainToolBar->addAction(helpAction);
    mainToolBar->addAction(startAction);

    graphToolBar = this->addToolBar(tr("&Настройки графика"));
            //new QToolBar(tr("&Настройки графика"), this);
    //this->addToolBar(Qt::BottomToolBarArea,toolb_settings);


    graphToolBar->addAction(drawNodeAction);
    graphToolBar->addSeparator();
    graphToolBar->addAction(drawXAction);
    graphToolBar->addAction(drawYAction);
    graphToolBar->addAction(drawZAction);
    graphToolBar->addSeparator();
    graphToolBar->addAction(fastModeAction);

}

void MainWindow::createStatusBar()
{
    this->statusBar()->show();
}

void MainWindow::saveSettings()
{
    QSettings settings("Software Ram2406", "ModelProc");
    settings.setValue("geometry", saveGeometry());
    //settings.setValue("mainToolBarGeometry", mainToolBar->geometry());
    //settings.setValue("mainToolBarState", mainToolBar->geometry());

    settings.setValue("state", this->saveState());
    //settings.setValue("dc1/float", this->dc1->isFloating());
    //settings.setValue("dc1/geom", this->dc1->saveGeometry());
    //settings.setValue("dc2/geom", this->dc2->saveGeometry());
    this->settings.writeSettings(settings);

}

void MainWindow::loadSettings()
{
    return;
    QSettings settings("Software Ram2406", "ModelProc");
    restoreGeometry(settings.value( "geometry").toByteArray());

    //mainToolBar->restoreGeometry(settings.value("mainToolBarGeometry").toByteArray());
    //graphToolBar->restoreGeometry(settings.value("graphToolBarGeometry").toByteArray());

    this->restoreState( settings.value("state").toByteArray() );

    //dc1->setFloating( settings.value("dc1/float").toBool());
    //dc1->restoreGeometry( settings.value("dc1/geom").toByteArray());
    //dc2->restoreGeometry( settings.value("dc2/geom").toByteArray());

    this->settings.readSettings(settings);




    if(this->settings.validate()) this->startAction->setEnabled(true);
}

void MainWindow::openFile()
{

    OpenFileForDemp o(this->settings,this);
    if( o.exec() ) startAction->setEnabled(true);

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
   // saveSettings();
}

void MainWindow::closeEvent(QCloseEvent *) {
    saveSettings();
}
