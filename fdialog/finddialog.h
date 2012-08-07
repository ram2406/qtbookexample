#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include <qdialog.h>
/*#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>*/

namespace Ui
{
    class FindDialog;
}

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;




class FindDialog : public QDialog
{
    Q_OBJECT

public:
    FindDialog(QWidget *parent = 0);
signals:
    void findNext(const QString &str,Qt::CaseSensitivity cs);
    void findPrev(const QString &str,Qt::CaseSensitivity cs);
private slots:
    void findClicked();
    void enableFindButton(const QString &text);

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *caseCheckBox;
    QCheckBox *backwardCheckBox;
    QPushButton *findButton;
    QPushButton *closeButton;

};

#endif // FINDDIALOG_H