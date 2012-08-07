#include <QtGui/QApplication>
#include "mainwindow.h"
//мои загатовки>
#include "gotocelldialog/gotocelldialog.h"
#include "fdialog/finddialog.h"
#include "sortdialog/sortdialog.h"
//<мои заготовки

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int i = 3;
    switch(i)
    {
        case 0: //стандартное отображение
        {
            MainWindow w;
            w.show();

        };break;
        case 1: //тест  GoToCellDialog
        {
            GoToCellDialog *dialog=  new GoToCellDialog;
            dialog->show();

        }; break;
        case 2: //тест  fdialog
        {
            FindDialog *dialog=  new FindDialog;
            dialog->show();


        }; break;
        case 3: //тест  sortdialog
        {
            SortDialog *dialog=  new SortDialog;
            //dialog->setColumnRange('A','Z');
            dialog->show();


        }; break;
        case 33:  break;
    }




    return a.exec();
}


//25.07.2012    прописал логику формы перейти к колонке
//              необходимо прописать логику формы сортировки
