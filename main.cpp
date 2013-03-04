#include <QtGui/QApplication>
#include "mainwindow.h"

#include "gotocelldialog/gotocelldialog.h"
#include "fdialog/finddialog.h"
#include "sortdialog/sortdialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int i = 0;
    switch(i)
    {
        case 0:
        {
            MainWindow *w = new MainWindow;
            w->show();

        };break;
        case 1:
        {
            GoToCellDialog *dialog=  new GoToCellDialog;
            dialog->show();

        };// break;
        case 2:
        {
            FindDialog *dialog=  new FindDialog;
            dialog->show();


        };// break;
        case 3:
        {
            SortDialog *dialog=  new SortDialog;
            //dialog->setColumnRange('A','Z');

            dialog->show();


        }; break;
        case 33:  break;
    }




    return a.exec();
}


//25.07.2012
//03.03.2013
//
