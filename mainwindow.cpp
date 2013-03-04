#include <QtGui>
#include "fdialog/finddialog.h"
#include "gotocelldialog/gotocelldialog.h"
#include "mainwindow.h"
#include "sortdialog/sortdialog.h"
#include "spreadsheet.h"

MainWindow::MainWindow()
{

    spreadsheet = new Spreadsheet;
    setCentralWidget(spreadsheet);

    createActions();
    createMenues();
    createContextMenu();
    createToolBars();
    createStatusBar();

    readSettings();
    findDialog =0;

    setWindowIcon(QIcon(":/Resource/excel.png"));
    setCurrentFile("");


}
void MainWindow::createActions()
{
    //file menu
    newAction = new QAction(tr("&New"),this);
    newAction->setIcon(QIcon(":/Resource/file-icon.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new spreadsheet file"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    for(int i=0; i < this->MaxRecentFiles; i++ ) {
        this->recentFileActions[i] = new QAction(this);
        this->recentFileActions[i]->setVisible(false);
        connect(this->recentFileActions[i]
                , SIGNAL(triggered())
                , this, SLOT(openRecentFile()));

    }

    this->exitAction = new QAction(tr("E&xit"),this);
    this->exitAction->setShortcut(tr("Ctrl+Q"));

    this->exitAction->setStatusTip(tr("Exit the application"));
    connect(this->exitAction,SIGNAL(triggered()),this,SLOT(close()));

    this->selectAllAction = new QAction(tr("&All"),this);
    this->selectAllAction->setShortcut(QKeySequence::SelectAll);
    connect(this->selectAllAction,SIGNAL(triggered()),spreadsheet,SLOT(selectAll()));

    this->showGridAction = new QAction(tr("&Show Grid"), this);
    showGridAction->setCheckable(true);
    showGridAction->setChecked(spreadsheet->showGrid());
    showGridAction->setStatusTip(tr("Show or hide the spreadsheet's"
                                    "grid"));
    connect(showGridAction, SIGNAL(toggled(bool))
            , spreadsheet,SLOT(setShowGrid(bool)));
    this->aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    this->saveAction = new QAction(tr("&Save"), this);
    saveAction->setStatusTip("Save document");
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setIcon(QIcon(tr(":/Resource/Actions-document-save-as-icon.png")));
    connect(saveAction,SIGNAL(triggered()), this, SLOT(save()));

    this->saveAsAction = new QAction(tr("&Save as"), this);
    saveAsAction->setStatusTip(tr("Save as.. document"));
    saveAsAction->setShortcut(tr("Ctrl+Shift+S"));
    connect(saveAsAction,SIGNAL(triggered()), this, SLOT(saveAs()));

    this->openAction = new QAction(tr("&Open"), this);
    openAction->setStatusTip(tr("Open the document"));
    openAction->setIcon(QIcon(tr(":/Resource/Files-Folder-icon.png")));
    openAction->setShortcut(tr("Ctrl+O"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    //edit menu
    this->cutAction = new QAction(tr("&Cut"), this);
    cutAction->setStatusTip( tr("Cut") );
    cutAction->setShortcut( tr("Ctrl+X") );
    //connect(cutAction, SIGNAL(triggered()), this, SLOT(cu))

    this->pasteAction        = new QAction(tr("&Paste"), this);
    pasteAction->setShortcut(tr("Ctrl+V"));
    this->copyAction         = new QAction(tr("C&opy"), this);
    copyAction->setShortcut(tr("Ctrl+C"));
    this->deleteAction       = new QAction(tr("&Delete"), this);
    deleteAction->setShortcut(tr("Del"));

    this->selectColumnAction = new QAction(tr("Select Column"), this);
    this->selectRowAction    = new QAction(tr("Select Row"), this);
    this->findAction         = new QAction(tr("Find"), this);
    this->goToCellAction     = new QAction(tr("Go to cell"), this);
    this->recalculateAction  = new QAction(tr("&Recalculate"), this);
    this->sortAction         = new QAction(tr("&Sort"), this);
    this->autoRecalcAction   = new QAction(tr("&Auto Recalculate"), this);
    this->aboutAction        = new QAction(tr("&About"), this);
}


void MainWindow::createMenues() {
    //file menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);

    fileMenu->addAction(openAction);

    fileMenu->addSeparator();

    fileMenu->addAction(saveAction);

    fileMenu->addAction(saveAsAction);
    separatorAction = fileMenu->addSeparator();

    for(int i = 0; i < this->MaxRecentFiles; i++) {
        fileMenu->addAction(recentFileActions[i]);
    }
    fileMenu->addSeparator();
    fileMenu->addAction((exitAction));

    //edit menu
    editMenu = this->menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);

    //select submenu
    this->selectSubMenu = editMenu->addMenu(tr("&Select"));

    //2013.03.03 page 71
    selectSubMenu->addAction(selectAllAction);
    selectSubMenu->addAction(selectColumnAction);
    selectSubMenu->addAction(selectRowAction);

    editMenu->addSeparator();
    editMenu->addAction(findAction);
    editMenu->addAction(goToCellAction);

    toolsMenu = this->menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(recalculateAction);
    toolsMenu->addAction(sortAction);

    optionsMenu = this->menuBar()->addMenu(tr("&Options"));
    optionsMenu->addAction(showGridAction);
    optionsMenu->addAction(autoRecalcAction);

    this->menuBar()->addSeparator();

    helpMenu = this->menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutQtAction);
    helpMenu->addAction(aboutAction);

}
void MainWindow::createContextMenu(){
    spreadsheet->addAction(cutAction);
    spreadsheet->addAction(copyAction);
    spreadsheet->addAction(pasteAction);
    spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createToolBars(){
    fileToolBar = this->addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    editToolBar = this->addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(findAction);
    editToolBar->addAction(goToCellAction);

}
void MainWindow::createStatusBar(){
    locationLabel = new QLabel(" W999 ");
    locationLabel->setAlignment(Qt::AlignCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);

    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(formulaLabel,1);

    connect(spreadsheet, SIGNAL(currentCellChanged(int,int,int,int))
            , this, SLOT(updateStatusBar()));
    connect(spreadsheet, SIGNAL(modeified())
            , this, SLOT(spreadsheetModified()) );

    updateStatusBar();
}

void MainWindow::readSettings(){}
void MainWindow::writeSettings(){}
bool MainWindow::okToContinue(){
    if(isWindowModified()) {
        int r = QMessageBox::warning(this, tr("Spreadsheet")
                                     , tr("The document has been modified. \n"
                                          "Do you want to save your changes?")
                                     , QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(r == QMessageBox::Yes) {
            return save();
        }
        if(r== QMessageBox::Cancel) {
            return false;
        }
        return true;

    }
}
bool MainWindow::loadFile(const QString &fileName){
    if(!spreadsheet->readFile(fileName)) {
        statusBar()->showMessage(tr("Loading canceled"), 2000);
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
    return false;
}
bool MainWindow::saveFile(const QString &fileName){
    if(!spreadsheet->writeFile(fileName)) {
        statusBar()->showMessage(tr("Saving canceled"),2000);
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;

}
void MainWindow::setCurrentFile(const QString &fileName){
    this->curFile = fileName;
    setWindowModified(false);

    QString showName = "Untitled";
    if(!curFile.isDetached()) {
        showName = strippedName(curFile);
        recentFiles.removeAll(curFile);
        recentFiles.prepend(curFile);;
        updateRecentFileActions();
    }
    setWindowTitle(tr("%1[*] - %2").arg(showName).arg(tr("Spreadsheet")));

}
void MainWindow::updateRecentFileActions(){
    QMutableStringListIterator i(recentFiles);
    while (i.hasNext()) {
        if(!QFile::exists(i.next())) {
            i.remove();
        }
    }
    for (int j=0; j< MaxRecentFiles; ++j) {
        if(j<recentFiles.count()) {
            QString text = tr("&%1 %2")
                           .arg(j+1)
                           .arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
            continue;
        }
        recentFileActions[j]->setVisible(false);
    }
    separatorAction->setVisible(!recentFiles.isEmpty());
}
QString MainWindow::strippedName(const QString &fullFileName){
    return QFileInfo(fullFileName).fileName();
}

//protected slots

void MainWindow::newFile(){
    if(okToContinue()) {
        spreadsheet->clear();
        setCurrentFile("");
    }
}
void MainWindow::open(){
    if(okToContinue()) {
        QString fileName = QFileDialog::getOpenFileName(this
                                        , tr("Open Spreadsheet"), "."
                                        , tr("Spreadsheet files (*.sp)\n"
                                             "Comma-separated values files (*.csv)\n"
                                             "Lotus 1-2-3 files (*.wk1, *.wks)"));
        if(!fileName.isEmpty())
            loadFile(fileName);
    }
}
bool MainWindow::save(){
    if(curFile.isEmpty()) {
        return saveAs();
    }
    return saveFile(curFile);
}
bool MainWindow::saveAs(){
    QString fileName = QFileDialog::getSaveFileName(this
                                   , tr("Save Spreadsheet")
                                   , tr("Spreadsheet files (*.sp)"));
    if(fileName.isEmpty())
        return false;

    return saveFile(fileName);
}
void MainWindow::find(){}
void MainWindow::goToCell(){}
void MainWindow::sort(){}
void MainWindow::about(){}
void MainWindow::openRecentFile(){
    if(okToContinue()) {
        QAction *action = qobject_cast<QAction*>(sender());
        if(action)
            loadFile(action ->data().toString());

    }
}
void MainWindow::updateStatusBar(){
    locationLabel->setText(spreadsheet->currentLocation());
    formulaLabel->setText(spreadsheet->currentFormula());
}
void MainWindow::spreadsheetModified(){
    setWindowModified(true);
    updateStatusBar();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if(okToContinue()) {
        writeSettings();
        event->accept();
    }
    event->ignore();

}
