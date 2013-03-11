#include "spreadsheet.h"
#include <QFile>
#include <QDataStream>
#include <QtGui>

Spreadsheet::Spreadsheet(QWidget *parent) :
    QTableWidget(parent), autoRecalc(true)
{
   //03/10/13 page 98
    setItemPrototype(new Cell);
    setSelectionMode(ContiguousSelection);
    connect(this, SIGNAL(itemChanged(QTableWidgetItem*))
            ,this, SLOT(somethingChanged()));
    clear();
}
void Spreadsheet::clear() {
    setRowCount(0);
    setColumnCount(0);
    setRowCount(RowCount);
    setColumnCount(ColumnCount);
    for(int i =0; i<ColumnCount; i++) {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(QString(QChar('A'+i)));
    }
    setCurrentCell(0,0);
}

QString Spreadsheet::currentLocation() const {
    /*return tr( "%1%2" )
            .arg(char( this->currentColumn() + 'A'))
            .arg(this->currentRow()+1);*/
    return QChar('A'+ currentColumn())+ QString::number(currentRow()+1);
}
QString Spreadsheet::currentFormula() const {
    /*return (this->currentItem() ? this->currentItem()->text() : "");*/
    return formula(currentRow(),currentColumn());
}
bool Spreadsheet::readFile(const QString &filename) {
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::Warning(this, tr("Spreadsheet")
                             ,tr("Cannot read file %1:\n%2.")
                             .arg(file.fileName()).arg(file.errorString()));
    }
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_8);

    quint32 magic;
    in >> magic;

    if(magic!= MagicNumber) {
        QMessageBox::warning(this, tr("Spreadsheet")
                             , tr("The file is not a Spreadsheet file."));
        return false;
    }
    clear();

    quint16 row
          , column;
    QString str;

    QApplication::setOverrideCursor(Qt::WhatsThisCursor);
    while(!in.atEnd()) {
        in >> row >> column >> str;
        setFormula(row, column, str);
    }
    QApplication::restoreOverrideCursor();
    return true;
}
bool Spreadsheet::writeFile(const QString &filename) {
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Spreadsheet")
                , tr("Cannot write file %1:\n%2.")
                    .arg(file.fileName()).arg(file.errorString()));
        return false;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint32(MagicNumber);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    for(int row = 0; row < RowCount; ++row) {
        for(int column = 0; column < ColumnCount; ++column) {
            QString str= formula(row, column);
            if(!str.isEmpty())
                out << quint16(row) << quint16(column) << str;
        }
    }
    QApplication::restoreOverrideCursor();
    return true;
}

QTableWidgetSelectionRange Spreadsheet::selectedRange() const {
    QList<QTableWidgetSelectionRange> ranges = selectedRanges();
    if(ranges.isEmpty())
        return QTableWidgetSelectionRange();
    return ranges.first();
}

void Spreadsheet::findNext(const QString &, Qt::CaseSensitivity) {}
void Spreadsheet::findPrevios(const QString &, Qt::CaseSensitivity) {}

void Spreadsheet::sort(const SpreadsheetCompare &compare) { }

void Spreadsheet::copy() {
    QTableWidgetSelectionRange range = selectedRange();
    QString str;
    for(int i=0; i < range.rowCount(); ++i) {
        if(i>0)
            str+="\n";
        for(int j=0; j<range.columnCount();++j) {
            if(j>0)
                str += "\t";
            str+=formula(range.topRow() + i, range.leftColumn() +j);

        }
    }
    QApplication::clipboard()->setText(str);
}
void Spreadsheet::cut()
{
    copy(); del();
}
void Spreadsheet::paste(){
    QTableWidgetSelectionRange range = selectedRange();
    QString str = QApplication::clipboard()->text();
    QStringList rows = str.split('\n');
    int numRows = rows.count();
    int numColumns = rows.first().count('\t') +1;
    if(range.rowCount() * range.columnCount() != 1
            && (range.columnCount() != numRows
                || range.columnCount() != numColumns) )  {
        QMessageBox::information((this, tr("Spreadsheet")
                                  , tr("The information cannot be pasted because the copy "
                                       "and paste areas aren't the same size.")));
        return;
    }
    for(int i=0; i < numRows; ++i) {
        QStringList columns = rows[i].split('\t');
        for(int j = 0; j < numColumns ; ++j) {
            int row = range.topRow() + i;
            int column = range.leftColumn() + j;
            if(row < RowCount && column < ColumnCount)
                setFormula(row, column, columns[j]);
        }
    }
    somethingChanged();
}
void Spreadsheet::del(){}
void Spreadsheet::selectCurentRow(){}
void Spreadsheet::selectCurrentColumn(){}
void Spreadsheet::recalculate(){}
void Spreadsheet::setAutoRecalculate(bool recalc){}

Cell *Spreadsheet::cell(int row, int column) const {
    return static_cast<Cell*> (item(row,column));
}
QString Spreadsheet::text(int row, int column) const {
    Cell *c= cell(row, column);
    if(c){
        return c->text();
    } else {
        return "";
    }
}
QString Spreadsheet::formula(int row, int column) const {
    Cell *c= cell(row, column);
    if(c) {
        return c->formula();
    } else {
        return "";
    }

}
void Spreadsheet::setFormula(int row, int column, const QString &formula) {
    Cell *c = cell(row, column);
    if(!c) {
        c = new Cell;
        setItem(row,column, c);
    }
    c->setFormula(formula);
}

void Spreadsheet::somethingChanged() {
    if(autoRecalc)
        recalculate();
    emit modeified();
}
