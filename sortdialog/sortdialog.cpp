#include "sortdialog.h"
#include <QtGui>

SortDialog::SortDialog(QWidget *parent):QDialog(parent)
{
    setupUi(this);

    secondaryGroupBox->hide();
    TretiaryGroupBox->hide();

    layout()->setSizeConstraint(QLayout::SetFixedSize);

    setColumnRange('A','Z');

}
void SortDialog::setColumnRange(QChar first, QChar last)
{
    primaryColumnCombo->clear();
    secondaryColumnCombo->clear();
    tretiaryColumnCombo->clear();

    secondaryColumnCombo->addItem(tr("None"));
    tretiaryColumnCombo->addItem(tr("None"));
    primaryColumnCombo->setMinimumSize(tretiaryColumnCombo->sizeHint());

    QChar ch = first;
    while(ch<=last)
    {
        primaryColumnCombo->addItem(QString(ch));
        secondaryColumnCombo->addItem(QString(ch));
        tretiaryColumnCombo->addItem(QString(ch));
        ch = ch.unicode()+1;
    }
    // comboBox
}
