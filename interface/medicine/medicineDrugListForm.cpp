#include "medicineDrugListForm.h"
#include "ui_medicineDrugListForm.h"
#include "medicineDrugForm.h"

#include "interface/utils.h"

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
    setupTableSettings();
    fillMedicinesTable(medicinesList);
}

MedicineDrugListForm::~MedicineDrugListForm() {
    delete ui;
}

void MedicineDrugListForm::addMedicineDrug(const Drug& newDrug) {
    ui->medicineTable->appendRow(newDrug, CreateRows::createMedicineDrugRow(newDrug));
}

void MedicineDrugListForm::editMedicineDrug(const Drug& drug) {
    ui->medicineTable->editData(drug, CreateRows::createMedicineDrugRow(drug));
}

void MedicineDrugListForm::onAddButtonClicked() {
    auto* medicineDrugForm = new MedicineDrugForm(database_);

    connect(medicineDrugForm, SIGNAL(medicineDrugCreateSignal(const medicine::Drug&)),
            this, SLOT(editMedicineDrug(const medicine::Drug&)));
    medicineDrugForm->setAttribute(Qt::WA_DeleteOnClose, true);
    medicineDrugForm->show();
}

void MedicineDrugListForm::onEditButtonClicked(const QVariant &data) {
    auto* medicineDrugForm = new MedicineDrugForm(database_, *getValueFromModelData<Drug>(data));

    connect(medicineDrugForm, SIGNAL(medicineDrugEditSignal(const medicine::Drug&)),
            this, SLOT(editMedicineDrug(const medicine::Drug&)));
    medicineDrugForm->setAttribute(Qt::WA_DeleteOnClose, true);
    medicineDrugForm->show();
}

void MedicineDrugListForm::onDeleteButtonClicked(const QVariant &data) {
    auto value = *getValueFromModelData<Drug>(data);
    database_->setDeletedMark(value, !value.isDeleted());
    editMedicineDrug(value);
}

void MedicineDrugListForm::setupTableSettings() {
    ui->medicineTable->setHorizontalHeaderLabels({"Название", "Торговые наименования", "Активное вещество", "Цена"});
    ui->medicineTable->setScale({4, 4, 4, 1});
    ui->medicineTable->setMainTabLabel("Лекарства");

    connect(ui->medicineTable, SIGNAL(onAddButtonClicked()),
            this, SLOT(onAddButtonClicked()));
    connect(ui->medicineTable, SIGNAL(onEditButtonClicked(const QVariant&)),
            this, SLOT(onEditButtonClicked(const QVariant&)));
    connect(ui->medicineTable, SIGNAL(onTableDoubleClicked(const QVariant&)),
            this, SLOT(onEditButtonClicked(const QVariant&)));
    connect(ui->medicineTable, SIGNAL(onDeleteButtonClicked(const QVariant&)),
            this, SLOT(onDeleteButtonClicked(const QVariant&)));
}

void MedicineDrugListForm::fillMedicinesTable(const std::vector<Drug>& medicinesList) {
    for (const auto& drug : medicinesList)
        addMedicineDrug(drug);
}
