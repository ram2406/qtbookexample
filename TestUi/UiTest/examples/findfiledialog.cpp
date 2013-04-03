#include "findfiledialog.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>



FindFileDialog::FindFileDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle("Find File Dialog");

    //widgets//
    QLabel *nameLabel = new QLabel(tr("Name:"), this);
    QLineEdit *nameLineEdit = new QLineEdit(this);

    QLabel *surnameLabel = new QLabel(tr("Surname:") ,this);
    QLineEdit *surnameLineEdit = new QLineEdit(this);

    QLabel *ageLabel = new QLabel(tr("Age:"), this);
    QLineEdit *ageLineEdit = new QLineEdit(this);

    QLabel *postLabel = new QLabel(tr("Post:"), this);
    QLineEdit *postLineEdit = new QLineEdit(this);

    QPushButton *okButton = new QPushButton(tr("OK"), this);
    QPushButton *cancelButton = new QPushButton(tr("Cancel"), this);
    QPushButton *cleanButton = new QPushButton(tr("Clean"), this );
    //widgets//



    QGridLayout *left = new QGridLayout;
    left->addWidget(nameLabel, 0,0);
    left->addWidget(nameLineEdit, 0,1);
    left->addWidget(surnameLabel, 1,0);
    left->addWidget(surnameLineEdit, 1,1);
    left->addWidget(ageLabel);
    left->addWidget(ageLineEdit);
    left->addWidget(postLabel);
    left->addWidget(postLineEdit);



    QVBoxLayout *right = new QVBoxLayout;
    right->addWidget(okButton);
    right->addWidget(cancelButton);
    right->addStretch();
    right->addWidget(cleanButton);

    QHBoxLayout *main = new QHBoxLayout;
    main->addLayout(left);
    main->addLayout(right);

    this->setLayout(main);

}
