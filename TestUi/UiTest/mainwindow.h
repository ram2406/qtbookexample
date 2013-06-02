#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include "plotter.h"
#include "ProgSettings.h"

class QTableWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    void loadCLDATA();
    void interpolExec();
    void loadGraph();
    void help();

    void setDrawNode(bool value);
    void setShowNodeX(bool value);
    void setShowNodeY(bool value);
    void setShowNodeZ(bool value);

    void exec();

private:
    void closeEvent(QCloseEvent *);

    void createCentralWidget();

    void loadGraphDemp(std::wstring dempFileName, Plotter *pl);
    void loadGraphInterpol(std::wstring interpolFileName, Plotter *pl);
    void loadGraphTopView(std::wstring dempFileName, Plotter *pl);
    void loadGraphSideView(std::wstring dempFileName, Plotter *pl);

    void createActions();
    void createMenues();
    //void createContextMenu();
    void createToolBars();
    void createStatusBar();

    void saveSettings();
    void loadSettings();

    QAction *settingsAction;
    QAction *closeAction;


    QAction *helpAction;


    QAction *drawXAction;
    QAction *drawYAction;
    QAction *drawZAction;

    QAction *fastModeAction;
    QAction *drawNodeAction;

    QAction *startAction;

    QTableWidget *table;
    Plotter *plDemp;

    Plotter *plInterpol;
    Plotter *plTopView;
    Plotter *plSideView;


    bool showX, showY , showZ , showNode;

    ProgSettings settings;

    QToolBar *mainToolBar;
    QToolBar *graphToolBar;


private slots:
    void openFile();
    void saveFile();


};

#endif // MAINWINDOW_H
