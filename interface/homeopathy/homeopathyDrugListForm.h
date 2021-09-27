#pragma once

#include "drugs/homeopathy.h"
#include "interface/basicForms/mappTable.h"

#include "database/databaseInterface.h"

#include <QStandardItem>
#include <QWidget>

namespace Ui {
class HomeopathyDrugListForm;
}

class HomeopathyDrugListForm : public QWidget {
    Q_OBJECT

public:
    explicit HomeopathyDrugListForm(DatabasePtr database,
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

private:
    Ui::HomeopathyDrugListForm *ui;
    DatabasePtr database_;
    std::shared_ptr<QStandardItemModel> tableViewModel_;
};
