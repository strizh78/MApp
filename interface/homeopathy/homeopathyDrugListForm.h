#pragma once

#include "drugs/homeopathy.h"
#include "interface/basicForms/mappTable.h"

#include "database/databaseinterface.h"

#include <QStandardItem>
#include <QWidget>

namespace Ui {
class HomeopathyDrugListForm;
}

class HomeopathyDrugListForm : public QWidget {
    Q_OBJECT

public:
    explicit HomeopathyDrugListForm(std::shared_ptr<DatabaseInterface> database,
                                    QWidget *parent = nullptr);
    ~HomeopathyDrugListForm();

private slots:
    void onAddButtonClicked();
    void onEditButtonClicked(const QVariant &data);
    void onDeleteButtonClicked(const QVariant &data);
    void addHomeopathyDrug(const homeopathy::Drug &newDrug);
    void editHomeopathyDrug(const homeopathy::Drug &editedDrug);

private:
    void setupTableSettings();
    void fillHomeopathyTable(const std::vector<homeopathy::Drug> &homeopatyList);
    QList<QStandardItem*> createHomeopathyDrugRow(const homeopathy::Drug &drug);

private:
    Ui::HomeopathyDrugListForm *ui;
    std::shared_ptr<DatabaseInterface> database_;
    std::shared_ptr<QStandardItemModel> tableViewModel_;
};
