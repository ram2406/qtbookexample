#include <QtGui/QApplication>
#include "mainwindow.h"
//��� ���������>
#include "gotocelldialog/gotocelldialog.h"
#include "fdialog/finddialog.h"
#include "sortdialog/sortdialog.h"
//<��� ���������

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int i = 1;
    switch(i)
    {
        case 0: //����������� �����������
        {
            MainWindow w;
            w.show();

        };break;
        case 1: //����  GoToCellDialog
        {
            GoToCellDialog *dialog=  new GoToCellDialog;
            dialog->show();

        }; break;
        case 2: //����  fdialog
        {
            FindDialog *dialog=  new FindDialog;
            dialog->show();


        }; break;
        case 3: //����  sortdialog
        {
            SortDialog *dialog=  new SortDialog;
            //dialog->setColumnRange('A','Z');
            dialog->show();


        }; break;
        case 33:  break;
    }




    return a.exec();
}


//25.07.2012    �������� ������ ����� ������� � �������
//              ���������� ��������� ������ ����� ����������
