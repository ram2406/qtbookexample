#include "spreadsheet.h"


Spreadsheet::Spreadsheet(QWidget *parent) :
    QTableWidget(parent)
{
   //03/10/13 page 98
}
QString Spreadsheet::currentLocation() const {
    return tr( "%1%2" )
            .arg(char( this->currentColumn() + 'A'))
            .arg(this->currentRow()+1);
}
QString Spreadsheet::currentFormula() const {
    return (this->currentItem() ? this->currentItem()->text() : "");
}
bool Spreadsheet::readFile(const QString &filename) {
}
bool Spreadsheet::writeFile(const QString &filename) {
}

void Spreadsheet::findNext(const QString &, Qt::CaseSensitivity) {}
void Spreadsheet::findPrevios(const QString &, Qt::CaseSensitivity) {}

void Spreadsheet::sort(const SpreadsheetCompare &compare) { }

void Spreadsheet::copy() {}
void Spreadsheet::cut(){}
void Spreadsheet::paste(){}
void Spreadsheet::del(){}
void Spreadsheet::selectCurentRow(){}
void Spreadsheet::selectCurrentColumn(){}
void Spreadsheet::recalculate(){}
void Spreadsheet::setAutoRecalculate(bool recalc){}

Cell *Spreadsheet::cell(int row, int column) const {}
QString Spreadsheet::text(int row, int column) const {}
QString Spreadsheet::formula(int row, int column) const {}
void Spreadsheet::setFormula(int row, int column, const QString &formula) {}

void Spreadsheet::somethingChanged() {}
