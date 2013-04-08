#include "openfilefordemp.h"
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QStyle>
#include <QFont>
#include <QPushButton>

OpenFileForDemp::OpenFileForDemp(QWidget *parent) :
    QDialog(parent)
{

    QLabel *openFileLabel = new QLabel(this);
    openFileLabel->setText(tr("Открыть файл для демпфирования:"));

    QLineEdit *openFileLineEdit = new QLineEdit(this);
    //openFileLineEdit->setText(tr("Пропишите путь или нажмите \"Обзор...\""));
    //openFileLineEdit->setStyleSheet(tr("QLineEdit { color: darkgray; font:italic}"));

    QPushButton *openFileButton = new QPushButton(tr("Обзор..."), this);

    QLabel *df1Label = new QLabel(this);
    df1Label->setText(tr("DF1 = "));

    QLineEdit *df1LineEdit = new QLineEdit(this);
    df1LineEdit->setInputMask(tr("00000000.00"));

    QLabel *df2Label = new QLabel(this);
    df2Label->setText(tr("DF2 = "));



    QLineEdit *df2LineEdit = new QLineEdit(this);
    df2LineEdit->setInputMask(tr("00000000.00"));



    QLabel *saveFileLabel = new QLabel(this);
    saveFileLabel->setText(tr("Сохранить файл после демпфирования:"));


    QLineEdit *saveFileLineEdit = new QLineEdit(this);
    //saveFileLineEdit->setText(tr("Пропишите путь или нажмите \"Обзор...\""));
    //saveFileLineEdit->setStyleSheet(tr("QLineEdit { color: darkgray; font:italic}"));
    QPushButton *saveFileButton = new QPushButton(tr("Обзор..."), this);


    QGridLayout *main = new QGridLayout(this);


    QPushButton *okButton       = new QPushButton(this);
    okButton->setText(tr("OK"));
    QPushButton *cancelButton   = new QPushButton(this);
    cancelButton->setText(tr("Отмена"));

    main->setMargin(12);

    main->addWidget(openFileLabel,      0,0);
    main->addWidget(openFileLineEdit ,  0,1);
    main->addWidget(openFileButton ,    0,2);

    main->addWidget(saveFileLabel ,     1,0);
    main->addWidget(saveFileLineEdit,   1,1);
    main->addWidget(saveFileButton,     1,2);

    main->addWidget(df1Label, 2,0, Qt::AlignRight);
    main->addWidget(df1LineEdit, 2,1);
    main->addWidget(df2Label, 3,0, Qt::AlignRight);
    main->addWidget(df2LineEdit, 3,1);

    main->addWidget(okButton, 4,1);
    main->addWidget(cancelButton, 4,2, Qt::AlignRight);

    this->setLayout(main);

}
