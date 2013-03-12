#ifndef CELL_H
#define CELL_H

#include <QTableWidgetItem>

class Cell : public QTableWidgetItem
{

public:
    explicit Cell();
    QString formula() { return text();}
    void setFormula(const QString& s){ this->setText(s);}
    void setDrity() {}
signals:
    
public slots:
    
};

#endif // CELL_H
