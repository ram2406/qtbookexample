#ifndef CELL_H
#define CELL_H

#include <QTableWidgetItem>

class Cell : public QTableWidgetItem
{

public:
    explicit Cell();
    QString formula() { return "";}
    void setFormula(const QString& ){}
signals:
    
public slots:
    
};

#endif // CELL_H
