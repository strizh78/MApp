#include "medicineDrugListForm.h"
#include "ui_medicineDrugListForm.h"
#include "medicineDrugForm.h"
#include "medicineTableSettingsForm.h"

#include <QSortFilterProxyModel>

#include <numeric>

using namespace medicine;

MedicineDrugListForm::MedicineDrugListForm(std::shared_ptr<DatabaseInterface> database,
                                           QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MedicineDrugListForm)
    , database_(database)
{
    ui->setupUi(this);

    std::vector<Drug> medicinesList;
    database->medicineDrugs(medicinesList);
    fillMedicinesTable(medicinesList);
}

MedicineDrugListForm::~MedicineDrugListForm() {
    delete ui;
}

void MedicineDrugListForm::on_createBtn_clicked() {
    auto* medicineDrugForm = new MedicineDrugForm(database_);

    connect(medicineDrugForm, SIGNAL(medicineDrugCreateSignal(const medicine::Drug&)),
            this, SLOT(addMedicineDrug(const medicine::Drug&)));
    medicineDrugForm->setAttribute(Qt::WA_DeleteOnClose, true);
    medicineDrugForm->show();
}

void MedicineDrugListForm::on_searchLine_textEdited(const QString &searchString) {
    searchInTable(searchString);
}

void MedicineDrugListForm::on_toolButton_clicked() {
    auto* medicineTableSettingsForm = new MedicineTableSettingsForm(ui->medicinesTable->horizontalHeader(), this);
    medicineTableSettingsForm->setAttribute(Qt::WA_DeleteOnClose, true);
    medicineTableSettingsForm->show();
}

void MedicineDrugListForm::addMedicineDrug(const Drug& newDrug) {
    tableViewModel_->appendRow(createMedicineDrugRow(tableViewModel_->rowCount(), newDrug));
}

void MedicineDrugListForm::editMedicineDrug(const Drug& oldDrug, const Drug& editedDrug) {
    for (int i = 0; i < tableViewModel_->rowCount(); ++i) {
        auto tableElement = tableViewModel_->index(i, 0);

        if (tableElement.data(Qt::UserRole).value<Drug>() == oldDrug) {
            tableViewModel_->removeRow(i);
            tableViewModel_->insertRow(i, createMedicineDrugRow(i, editedDrug));
            ui->medicinesTable->clearSelection();
            return;
        }
    }
}

void MedicineDrugListForm::on_medicinesTable_doubleClicked(const QModelIndex &index) {
    const QModelIndex& firstIndex = ui->medicinesTable->model()->index(index.row(), 0);
    auto* medicineDrugForm = new MedicineDrugForm(database_, firstIndex.data(Qt::UserRole).value<Drug>());

    connect(medicineDrugForm, SIGNAL(medicineDrugEditSignal(const medicine::Drug&, const medicine::Drug&)),
            this, SLOT(editMedicineDrug(const medicine::Drug&, const medicine::Drug&)));
    medicineDrugForm->setAttribute(Qt::WA_DeleteOnClose, true);
    medicineDrugForm->show();
}

void MedicineDrugListForm::resizeEvent(QResizeEvent *event) {
    static const std::vector<int> scale = {4, 4, 1};
    static const int dimension = std::accumulate(scale.begin(), scale.end(), 0);
    static const int columnNumber = tableViewModel_->columnCount();
    static const int baseWidth = (ui->medicinesTable->width() - 10 * columnNumber) / dimension;

    for (int column = 0; column < columnNumber; ++column) {
        ui->medicinesTable->setColumnWidth(column, baseWidth * scale[column]);
    }

    QWidget::resizeEvent(event);
}

void MedicineDrugListForm::searchInTable(const QString& searchString) {
    if (tableViewModel_.get() != ui->medicinesTable->model()) {
        delete ui->medicinesTable->model();
    }

    auto* proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(tableViewModel_.get());
    ui->medicinesTable->setModel(proxyModel);

    QRegExp regExp(searchString,
                   Qt::CaseInsensitive,
                   QRegExp::PatternSyntax(QRegExp::RegExp)
                   );
    proxyModel->setFilterKeyColumn(0);
    proxyModel->setFilterRegExp(regExp);
}

void MedicineDrugListForm::fillMedicinesTable(const std::vector<Drug>& medicinesList) {
    tableViewModel_ = std::make_shared<QStandardItemModel>();

    static const QStringList columnNames = {"Торговые наименования", "Активное вещество", "Цена"};
    tableViewModel_->setHorizontalHeaderLabels(columnNames);

    for (const auto& drug : medicinesList) {
        addMedicineDrug(drug);
    }

    ui->medicinesTable->setModel(tableViewModel_.get());
}

QList<QStandardItem*> MedicineDrugListForm::createMedicineDrugRow(size_t row, const Drug& drug) {
    QList<QStandardItem*> lst;

    QStandardItem* brands = new QStandardItem(row, 0);
    brands->setText(drug.getBrands(", "));
    brands->setData(QVariant::fromValue(drug), Qt::UserRole);

    QStandardItem* name = new QStandardItem(row, 1);
    name->setText(drug.getFullName());

    QStandardItem* price = new QStandardItem(row, 2);
    price->setText(QString::number(drug.price()));

    lst << brands << name << price;
    return lst;
}
