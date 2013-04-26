#ifndef OPENFILEFORDEMP_H
#define OPENFILEFORDEMP_H

#include <QLabel>
#include <QGridLayout>
#include <QStyle>
#include <QFont>
#include <QPushButton>
#include <QFile>
#include <QDialog>
#include <QLineEdit>
#include "ProgSettings.h"

class OpenFileForDemp : public QDialog
{
    Q_OBJECT
public:
    explicit OpenFileForDemp(ProgSettings &ps, QWidget *parent = 0 );

signals:
    
public slots:
    void accept();
    void cancel();

    void browseCLDataFile();
    void browseInterFile();
    void browseDempFile();

private:
    QLineEdit *clDataFileLineEdit;
    QPushButton *clDataFileButton;
    QLineEdit *interFileLineEdit;
    QLineEdit *df1LineEdit ;
    QPushButton *interFileButton ;
    QLineEdit *df2LineEdit;
    QLineEdit *dempFileLineEdit;
    QPushButton *dempFileButton;
    ProgSettings &ps;

    const ProgSettings old_ps;

};

#endif // OPENFILEFORDEMP_H
