#pragma once

#include "drugs/medicines.h"

#include "database/databaseinterface.h"

#include <QWidget>
#include <QStandardItemModel>
#include <QStyledItemDelegate>

#include <memory>
#include <vector>

namespace Ui {
class MedicineDrugListForm;
}

class MedicineDrugListForm : public QWidget
{
    Q_OBJECT

public:
    explicit MedicineDrugListForm(std::shared_ptr<DatabaseInterface> database,
                           QWidget *parent = nullptr);
    ~MedicineDrugListForm();

private slots:
    void on_createBtn_clicked();
    void on_deleteBtn_clicked();
    void on_searchLine_textEdited(const QString &searchString);
    void on_toolButton_clicked();

    void addMedicineDrug(const medicine::Drug& newDrug);
    void editMedicineDrug(const medicine::Drug& oldDrug, const medicine::Drug& editedDrug);
    void on_medicinesTable_doubleClicked(const QModelIndex &index);

private:
    void resizeEvent(QResizeEvent *event) override;
    void searchInTable(const QString& searchString);
    void fillMedicinesTable(const std::vector<medicine::Drug>& medicinesList);
    QList<QStandardItem*> createMedicineDrugRow(size_t row, const medicine::Drug& drug);

    Ui::MedicineDrugListForm *ui;
    std::shared_ptr<DatabaseInterface> database_;
    std::shared_ptr<QStandardItemModel> tableViewModel_;
};

