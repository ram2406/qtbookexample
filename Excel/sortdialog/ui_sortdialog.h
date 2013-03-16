/********************************************************************************
** Form generated from reading UI file 'sortdialog.ui'
**
** Created: Tue Aug 7 22:27:39 2012
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SORTDIALOG_H
#define UI_SORTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *primaryGroupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *primaryColumnCombo;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QComboBox *primaryOrderCombo;
    QVBoxLayout *verticalLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *verticalSpacer;
    QPushButton *cancelButton_2;
    QGroupBox *TretiaryGroupBox;
    QGridLayout *gridLayout_3;
    QLabel *label_5;
    QComboBox *tretiaryColumnCombo;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_6;
    QComboBox *tretiaryOrderCombo;
    QGroupBox *secondaryGroupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QComboBox *secondaryColumnCombo;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_4;
    QComboBox *secondaryOrderCombo;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(303, 286);
        Dialog->setMinimumSize(QSize(303, 286));
        gridLayout_4 = new QGridLayout(Dialog);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        primaryGroupBox = new QGroupBox(Dialog);
        primaryGroupBox->setObjectName(QString::fromUtf8("primaryGroupBox"));
        gridLayout = new QGridLayout(primaryGroupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(primaryGroupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        primaryColumnCombo = new QComboBox(primaryGroupBox);
        primaryColumnCombo->setObjectName(QString::fromUtf8("primaryColumnCombo"));

        gridLayout->addWidget(primaryColumnCombo, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(77, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        label_2 = new QLabel(primaryGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        primaryOrderCombo = new QComboBox(primaryGroupBox);
        primaryOrderCombo->setObjectName(QString::fromUtf8("primaryOrderCombo"));

        gridLayout->addWidget(primaryOrderCombo, 1, 1, 1, 2);


        gridLayout_4->addWidget(primaryGroupBox, 0, 0, 3, 2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        okButton = new QPushButton(Dialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        verticalLayout->addWidget(okButton);

        cancelButton = new QPushButton(Dialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        verticalLayout->addWidget(cancelButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        cancelButton_2 = new QPushButton(Dialog);
        cancelButton_2->setObjectName(QString::fromUtf8("cancelButton_2"));

        verticalLayout->addWidget(cancelButton_2);


        gridLayout_4->addLayout(verticalLayout, 0, 2, 4, 1);

        TretiaryGroupBox = new QGroupBox(Dialog);
        TretiaryGroupBox->setObjectName(QString::fromUtf8("TretiaryGroupBox"));
        gridLayout_3 = new QGridLayout(TretiaryGroupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_5 = new QLabel(TretiaryGroupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 0, 0, 1, 1);

        tretiaryColumnCombo = new QComboBox(TretiaryGroupBox);
        tretiaryColumnCombo->setObjectName(QString::fromUtf8("tretiaryColumnCombo"));

        gridLayout_3->addWidget(tretiaryColumnCombo, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        label_6 = new QLabel(TretiaryGroupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 1, 0, 1, 1);

        tretiaryOrderCombo = new QComboBox(TretiaryGroupBox);
        tretiaryOrderCombo->setObjectName(QString::fromUtf8("tretiaryOrderCombo"));

        gridLayout_3->addWidget(tretiaryOrderCombo, 1, 1, 1, 2);


        gridLayout_4->addWidget(TretiaryGroupBox, 6, 0, 1, 2);

        secondaryGroupBox = new QGroupBox(Dialog);
        secondaryGroupBox->setObjectName(QString::fromUtf8("secondaryGroupBox"));
        secondaryGroupBox->setEnabled(true);
        gridLayout_2 = new QGridLayout(secondaryGroupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_3 = new QLabel(secondaryGroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        secondaryColumnCombo = new QComboBox(secondaryGroupBox);
        secondaryColumnCombo->setObjectName(QString::fromUtf8("secondaryColumnCombo"));

        gridLayout_2->addWidget(secondaryColumnCombo, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        label_4 = new QLabel(secondaryGroupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        secondaryOrderCombo = new QComboBox(secondaryGroupBox);
        secondaryOrderCombo->setObjectName(QString::fromUtf8("secondaryOrderCombo"));

        gridLayout_2->addWidget(secondaryOrderCombo, 1, 1, 1, 2);


        gridLayout_4->addWidget(secondaryGroupBox, 4, 0, 1, 2);

        QWidget::setTabOrder(primaryColumnCombo, primaryOrderCombo);
        QWidget::setTabOrder(primaryOrderCombo, secondaryColumnCombo);
        QWidget::setTabOrder(secondaryColumnCombo, secondaryOrderCombo);
        QWidget::setTabOrder(secondaryOrderCombo, tretiaryColumnCombo);
        QWidget::setTabOrder(tretiaryColumnCombo, tretiaryOrderCombo);
        QWidget::setTabOrder(tretiaryOrderCombo, okButton);
        QWidget::setTabOrder(okButton, cancelButton);
        QWidget::setTabOrder(cancelButton, cancelButton_2);

        retranslateUi(Dialog);
        QObject::connect(okButton, SIGNAL(clicked()), Dialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), Dialog, SLOT(reject()));
        QObject::connect(cancelButton_2, SIGNAL(toggled(bool)), secondaryGroupBox, SLOT(setVisible(bool)));
        QObject::connect(cancelButton_2, SIGNAL(toggled(bool)), TretiaryGroupBox, SLOT(setVisible(bool)));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        primaryGroupBox->setTitle(QApplication::translate("Dialog", "&Primary Key", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "Column:", 0, QApplication::UnicodeUTF8));
        primaryColumnCombo->clear();
        primaryColumnCombo->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "None", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("Dialog", "Order:", 0, QApplication::UnicodeUTF8));
        primaryOrderCombo->clear();
        primaryOrderCombo->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "Asceding", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Dialog", "Disceding", 0, QApplication::UnicodeUTF8)
        );
        okButton->setText(QApplication::translate("Dialog", "OK", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("Dialog", "Cancel", 0, QApplication::UnicodeUTF8));
        cancelButton_2->setText(QApplication::translate("Dialog", "More", 0, QApplication::UnicodeUTF8));
        TretiaryGroupBox->setTitle(QApplication::translate("Dialog", "&Tretiary Key", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Dialog", "Column:", 0, QApplication::UnicodeUTF8));
        tretiaryColumnCombo->clear();
        tretiaryColumnCombo->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "None", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("Dialog", "Order:", 0, QApplication::UnicodeUTF8));
        tretiaryOrderCombo->clear();
        tretiaryOrderCombo->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "Asceding", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Dialog", "Disceding", 0, QApplication::UnicodeUTF8)
        );
        secondaryGroupBox->setTitle(QApplication::translate("Dialog", "&Secondary Key", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Dialog", "Column:", 0, QApplication::UnicodeUTF8));
        secondaryColumnCombo->clear();
        secondaryColumnCombo->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "None", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("Dialog", "Order:", 0, QApplication::UnicodeUTF8));
        secondaryOrderCombo->clear();
        secondaryOrderCombo->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "Asceding", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Dialog", "Disceding", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SORTDIALOG_H
