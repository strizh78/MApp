#pragma once

#include "drugs/medicines.h"
#include "interface/basicForms/mappTable.h"

#include "database/databaseInterface.h"

#include <QStandardItemModel>
#include <QWidget>

#include <memory>
#include <vector>

namespace Ui {
class MedicineDrugListForm;
}

class MedicineDrugListForm : public QWidget {
    Q_OBJECT

public:
    explicit MedicineDrugListForm(DatabasePtr database,
                           QWidget *parent = nullptr);
    ~MedicineDrugListForm();

private slots:
    void onAddButtonClicked();
    void onEditButtonClicked(const QVariant &data);
    void onDeleteButtonClicked(const QVariant &data);
    void addMedicineDrug(const medicine::Drug& drug);
    void editMedicineDrug(const medicine::Drug& drug);

private:
    void setupTableSettings();
    void fillMedicinesTable(const std::vector<medicine::Drug>& medicinesList);

    Ui::MedicineDrugListForm *ui;
    DatabasePtr database_;
};

