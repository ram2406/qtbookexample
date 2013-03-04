#include <QtGui>
 #include <QtSql>

 #include "tableeditor.h"

 TableEditor::TableEditor(const QString &tableName, QWidget *parent)
     : QDialog(parent)
 {
     model = new QSqlTableModel(this);
     model->setTable(tableName);
     model->setEditStrategy(QSqlTableModel::OnManualSubmit);
     model->select();

     //model->setHeaderData(0, Qt::Horizontal, tr("ID"));
     //model->setHeaderData(1, Qt::Horizontal, tr("First name"));
     //model->setHeaderData(2, Qt::Horizontal, tr("Last name"));

     QTableView *view = new QTableView;
     view->setModel(model);

     submitButton = new QPushButton(tr("Submit"));
     submitButton->setDefault(true);
     revertButton = new QPushButton(tr("&Revert"));
     quitButton = new QPushButton(tr("Quit"));

     buttonBox = new QDialogButtonBox(Qt::Vertical);
     buttonBox->addButton(submitButton, QDialogButtonBox::ActionRole);
     buttonBox->addButton(revertButton, QDialogButtonBox::ActionRole);
     buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

     connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));
     connect(revertButton, SIGNAL(clicked()), model, SLOT(revertAll()));
     connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

     QHBoxLayout *mainLayout = new QHBoxLayout;
     mainLayout->addWidget(view);
     mainLayout->addWidget(buttonBox);
     setLayout(mainLayout);

     setWindowTitle(tr("Cached Table"));
 }

 void TableEditor::submit()
 {
     model->database().transaction();
     if (model->submitAll()) {
         model->database().commit();
     } else {
         model->database().rollback();
         QMessageBox::warning(this, tr("Cached Table"),
                              tr("The database reported an error: %1")
                              .arg(model->lastError().text()));
     }
 }
