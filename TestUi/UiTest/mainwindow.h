#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    
private:
    void createCentralWidget();

    void createActions();
    void createMenues();
    //void createContextMenu();
    void createToolBars();
    void createStatusBar();

    QAction *openFileAction;
    QAction *closeAction;
    QAction *saveFileAction;
    QAction *aboutAction;


private slots:
    void openFile();
    void saveFile();


};

#endif // MAINWINDOW_H
