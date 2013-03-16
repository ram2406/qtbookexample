#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include "ui_sortdialog.h"
#include <QDialog>

class SortDialog:public QDialog, public Ui::Dialog
{
    Q_OBJECT
public:
    SortDialog(QWidget *parent=0);
    void setColumnRange(QChar first,QChar last);
};

#endif // SORTDIALOG_H
