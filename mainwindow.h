#ifndef MAINWINDOW_H
#define MAINWINDO
#include <QMainWindow>

class QAction;
class QLabel;
class FindDialog;
class Spreadsheet;


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();


protected:
    void closeEvent(QCloseEvent *);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void find();
    void goToCell();
    void sort();
    void about();
    void openRecentFile();
    void updateStatusBar();
    void spreadsheetModified();

private:
    void createActions();
    void createMenues();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool okToContinue();
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    QString strippedName(const QString &fullFileName);

    Spreadsheet *spreadsheet;
    FindDialog *findDialog;
    QLabel *locationLabel;
    QLabel *formulaLabel;

    QStringList recentFiles;
    QString curFile;

    enum { MaxRecentFiles = 5 };



    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *selectSubMenu;
    QMenu *toolsMenu;
    QMenu *optionsMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;

    QAction *newAction;
    QAction *openAction;
    QAction *aboutQtAction;
    QAction *exitAction;
    QAction *selectAllAction;
    QAction *showGridAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *deleteAction;

    QAction *selectRowAction;
    QAction *selectColumnAction;

    QAction *findAction;
    QAction *goToCellAction;

    QAction *recentFileActions[MaxRecentFiles];
    QAction *separatorAction;

    QAction *recalculateAction;
    QAction *sortAction;
    QAction *autoRecalcAction;
    QAction *aboutAction;
};

#endif // MAINWINDOW_H
