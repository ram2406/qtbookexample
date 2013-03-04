#include "spreadsheet.h"


Spreadsheet::Spreadsheet(QWidget *parent) :
    QTableWidget(parent)
{

}
QString Spreadsheet::currentLocation() {
    return "Unwork location!";
}
QString Spreadsheet::currentFormula() {
    return "Unwork formula!";
}
bool Spreadsheet::readFile(const QString &filename) {
}
bool Spreadsheet::writeFile(const QString &filename) {
}
