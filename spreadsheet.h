#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QTableWidget>

class Spreadsheet : public QTableWidget
{
    Q_OBJECT
public:
    explicit Spreadsheet(QWidget *parent = 0);
    QString currentLocation();
    QString currentFormula();
    bool readFile(const QString &filename);
    bool writeFile(const QString &filename);
signals:
    void modeified();
public slots:
    void findNext(const QString &, Qt::CaseSensitivity) {}
    void findPrevios(const QString &, Qt::CaseSensitivity) {}
};

#endif // SPREADSHEET_H
