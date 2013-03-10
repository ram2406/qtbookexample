#include "spreadsheet.h"


Spreadsheet::Spreadsheet(QWidget *parent) :
    QTableWidget(parent)
{

}
QString Spreadsheet::currentLocation() {
    return tr( "%1%2" )
            .arg(char( this->currentColumn() + 'A'))
            .arg(this->currentRow()+1);
}
QString Spreadsheet::currentFormula() {
    return (this->currentItem() ? this->currentItem()->text() : "");
}
bool Spreadsheet::readFile(const QString &filename) {
}
bool Spreadsheet::writeFile(const QString &filename) {
}
