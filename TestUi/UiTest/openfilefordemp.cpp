#include "openfilefordemp.h"
#include <QFileDialog>
#include "ProgSettings.h"

#include <QMessageBox>

#include <QFile>

OpenFileForDemp::OpenFileForDemp(ProgSettings &ps, QWidget *parent) :
    QDialog(parent), ps(ps), old_ps(ps)
{

    this->setWindowTitle(tr("Настройки приложения"));

    QGridLayout *main = new QGridLayout(this);

    {
    QLabel *openFileLabel = new QLabel(this);
    openFileLabel->setText(tr("Открыть файл содержащий CLDATA-код:"));

    clDataFileLineEdit = new QLineEdit(this);
    //openFileLineEdit->setText(tr("Пропишите путь или нажмите \"Обзор...\""));
    //openFileLineEdit->setStyleSheet(tr("QLineEdit { color: darkgray; font:italic}"));

    clDataFileButton = new QPushButton(tr("Обзор..."), this);
    connect(clDataFileButton , SIGNAL(clicked()), this, SLOT(browseCLDataFile()));

    main->addWidget(openFileLabel,      0,0, Qt::AlignRight);
    main->addWidget(clDataFileLineEdit ,  0,1);
    main->addWidget(clDataFileButton ,    0,2);

    }
    {
    QLabel *df1Label = new QLabel(this);
    df1Label->setText(tr("Минимальная скорость обработки станка:"));

    df1LineEdit = new QLineEdit(this);
    df1LineEdit->setInputMask(tr("00000000.00"));




    QLabel *df2Label = new QLabel(this);
    df2Label->setText(tr("Максимальная скорость обработки станка:"));

    df2LineEdit = new QLineEdit(this);
    df2LineEdit->setInputMask(tr("00000000.00"));

    main->addWidget(df1Label, 3,0, Qt::AlignRight);
    main->addWidget(df1LineEdit, 3,1);
    main->addWidget(df2Label, 4,0, Qt::AlignRight);
    main->addWidget(df2LineEdit, 4,1);

    }
    {
    QLabel *saveFileLabel = new QLabel(this);
    saveFileLabel->setText(tr("Сохранить файл после обработки интерполятором:"));


    interFileLineEdit = new QLineEdit(this);
    //saveFileLineEdit->setText(tr("Пропишите путь или нажмите \"Обзор...\""));
    //saveFileLineEdit->setStyleSheet(tr("QLineEdit { color: darkgray; font:italic}"));
    interFileButton = new QPushButton(tr("Обзор..."), this);
    connect(interFileButton , SIGNAL(clicked()), this, SLOT(browseInterFile()));


    main->addWidget(saveFileLabel ,     1,0, Qt::AlignRight);
    main->addWidget(interFileLineEdit,   1,1);
    main->addWidget(interFileButton,     1,2);

    }
    {
    QLabel *saveFileDempLabel = new QLabel(this);
    saveFileDempLabel->setText(tr("Сохранить файл после демпфирования:"));


    dempFileLineEdit = new QLineEdit(this);
    //saveFileLineEdit->setText(tr("Пропишите путь или нажмите \"Обзор...\""));
    //saveFileLineEdit->setStyleSheet(tr("QLineEdit { color: darkgray; font:italic}"));
    dempFileButton = new QPushButton(tr("Обзор..."), this);
    connect(dempFileButton , SIGNAL(clicked()), this, SLOT(browseDempFile()));

    main->addWidget(saveFileDempLabel ,     2,0, Qt::AlignRight);
    main->addWidget(dempFileLineEdit,   2,1);
    main->addWidget(dempFileButton,     2,2);
    }
    {

    QPushButton *okButton       = new QPushButton(this);
    okButton->setText(tr(" Сохранить настройки "));

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));

    QPushButton *cancelButton   = new QPushButton(this);
    cancelButton->setText(tr("Отмена"));

    connect( cancelButton , SIGNAL(clicked()) , this, SLOT(cancel()) );
    main->addWidget(okButton, 5,1);
    main->addWidget(cancelButton, 5,2, Qt::AlignRight);

    }

    main->setMargin(12);


    this->setLayout(main);

    if(ps.df1)
        this->df1LineEdit->setText( tr("%1").arg(ps.df1) );
    if(ps.df2)
        this->df2LineEdit->setText( tr("%1").arg(ps.df2) );

    this->dempFileLineEdit->setText(tr(ps.dempFileName.c_str()));
    this->interFileLineEdit->setText(tr(ps.interFileName.c_str()));
    this->clDataFileLineEdit->setText(tr(ps.clDataFileName.c_str()));

}


void OpenFileForDemp::accept() {

    ps.clDataFileName = clDataFileLineEdit->text().toStdString();
    ps.interFileName = interFileLineEdit->text().toStdString();
    ps.dempFileName = dempFileLineEdit->text().toStdString();

    ps.df1 = df1LineEdit->text().toDouble();
    ps.df2 = df2LineEdit->text().toDouble();

    if(!ps.validate()) {
        QMessageBox::information(this, tr("Проверка"), tr("Не все поля были введины"),QMessageBox::Ok);
        return;
    }

    QString message;

    QFile clDataFile(ps.clDataFileName.c_str());
    if(! clDataFile.exists() )
        message += tr("Не найден файл содержащий CLDATA-код :\n\t%1\n").arg(ps.clDataFileName.c_str());

    /*QFile interFile(ps.interFileName.c_str());
    if(! interFile.exists() )
        message += tr("Не найден файл содержащий управляющие сигналы после интерполяции :\n\t%1\n").arg(ps.interFileName.c_str());

    QFile dempFile(ps.dempFileName.c_str());
    if(! dempFile.exists() )
        message += tr("Не найден файл содержащий управляющие сигналы после интерполяции :\n\t%1\n").arg(ps.dempFileName.c_str());
    */

    if(ps.df1 > ps.df2)
        message += tr("Проверте значения скоростей : %1 > %2").arg(ps.df1 , ps.df2);


    if(!message.isEmpty()) {
        QMessageBox::information(this, tr("Проверка"), message, QMessageBox::Ok);
        return;
    }



/*
    df1 = saveFileLineEdit->text().toDouble(&res);

    if(res == false) return;

    df2 = openFileLineEdit->text().toDouble(&res);

    if(res == false ) return;

    if(openFileLineEdit->text().isEmpty() || !saveFileLineEdit->text().isEmpty()) return;
*/


    this->done(true);

}

void OpenFileForDemp::cancel()
{
    ps = old_ps;
    done(false);
}

void OpenFileForDemp::browseCLDataFile()
{
    clDataFileLineEdit->setText( QFileDialog::getOpenFileName(this, tr("Выберите файл содержащий CLDATA-код"), tr("."), tr("CLDATA (*.pl0)")) );
}

void OpenFileForDemp::browseInterFile()
{
    interFileLineEdit->setText( QFileDialog::getSaveFileName(this, tr("Выберите путь для сохранения файла после интерполяции"), tr("."), tr("INTERPOL (*.pl1)")) );
}

void OpenFileForDemp::browseDempFile()
{
    dempFileLineEdit->setText( QFileDialog::getSaveFileName(this, tr("Выберите путь для сохранения файла после демпфированрия"), tr("."), tr("DEMP (*.pl2)")) );
}
