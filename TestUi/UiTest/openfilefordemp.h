#ifndef OPENFILEFORDEMP_H
#define OPENFILEFORDEMP_H

#include <QDialog>

class OpenFileForDemp : public QDialog
{
    Q_OBJECT
public:
    explicit OpenFileForDemp(QWidget *parent = 0);
    
signals:
    
public slots:
    void accept() {}

};

#endif // OPENFILEFORDEMP_H
