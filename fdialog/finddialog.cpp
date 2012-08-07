#include <QtGui>
#include "fdialog/finddialog.h"

FindDialog::FindDialog(QWidget *parent):QDialog(parent)
{
    label = new QLabel(tr("Find &what:"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);

    caseCheckBox = new QCheckBox(tr("Match &case"));
    backwardCheckBox = new QCheckBox(tr("Search backward"));

    findButton = new QPushButton(tr("&Find"));
    findButton->setDefault(true);
    findButton->setEnabled(false);

    closeButton = new QPushButton(tr("Close"));

    connect(lineEdit,SIGNAL(textChanged(const QString &)),this,SLOT(enableFindButton(const QString &)));
    connect(findButton,SIGNAL(clicked()),this,SLOT(findClicked()));
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    QVBoxLayout *leftLayout= new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(backwardCheckBox);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    setWindowTitle("Find");
    setFixedHeight(sizeHint().height());

}
//вызывается при нажатии кнопки Find
void FindDialog::findClicked()
{
    QString text  = lineEdit->text();
    Qt::CaseSensitivity cs= caseCheckBox->isChecked() ?
                Qt::CaseSensitive:
                Qt::CaseInsensitive;
    if(backwardCheckBox->isChecked())
    {
        //генерирует сигнал
        emit findPrev(text,cs);
    }
    else
    {
        //генерирует сигнал
        emit findNext(text,cs);
    }
}
//если нет текста - кнопка не активна
void FindDialog::enableFindButton(const QString &text)
{
    findButton->setEnabled(!text.isEmpty());
}
