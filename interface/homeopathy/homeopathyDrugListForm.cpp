#include "homeopathyDrugListForm.h"
#include "ui_homeopathyDrugListForm.h"
#include "homeopathyDrugForm.h"

#include "interface/utils.h"

using namespace homeopathy;

HomeopathyDrugListForm::HomeopathyDrugListForm(DatabasePtr database,
                                               QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeopathyDrugListForm),
    database_(database)
{
    ui->setupUi(this);
    std::vector<Drug> homeopathyList;
    database->homeopathy->list(homeopathyList);
    setupTableSettings();
    fillHomeopathyTable(homeopathyList);
}

HomeopathyDrugListForm::~HomeopathyDrugListForm() {
    delete ui;
}

void HomeopathyDrugListForm::onAddButtonClicked() {
    auto* homeopathyDrugForm = new HomeopathyDrugForm(database_);

    connect(homeopathyDrugForm, SIGNAL(homeopathyDrugCreateSignal(const homeopathy::Drug&)),
            this, SLOT(addHomeopathyDrug(const homeopathy::Drug&)));
    homeopathyDrugForm->setAttribute(Qt::WA_DeleteOnClose, true);
    homeopathyDrugForm->show();
}

void HomeopathyDrugListForm::onEditButtonClicked(const QVariant &data) {
    auto* homeopathyDrugForm = new HomeopathyDrugForm(database_, *getValueFromModelData<Drug>(data));

    connect(homeopathyDrugForm, SIGNAL(homeopathyDrugEditSignal(const homeopathy::Drug&)),
            this, SLOT(editHomeopathyDrug(const homeopathy::Drug&)));
    homeopathyDrugForm->setAttribute(Qt::WA_DeleteOnClose, true);
    homeopathyDrugForm->show();
}

void HomeopathyDrugListForm::onDeleteButtonClicked(const QVariant& data) {
    auto value = *getValueFromModelData<Drug>(data);
    database_->homeopathy->setDeletedMark(value, !value.isDeleted());
    editHomeopathyDrug(value);
}

void HomeopathyDrugListForm::addHomeopathyDrug(const Drug& newDrug) {
    ui->homeopathyTable->appendRow(newDrug, CreateRows::createHomeopathyDrugRow(newDrug));
}

void HomeopathyDrugListForm::editHomeopathyDrug(const Drug& editedDrug) {
    ui->homeopathyTable->editData(editedDrug, CreateRows::createHomeopathyDrugRow(editedDrug));
}

void HomeopathyDrugListForm::setupTableSettings() {
    ui->homeopathyTable->setHorizontalHeaderLabels({"Наименования", "Группа"});
    ui->homeopathyTable->setScale({2, 1});
    ui->homeopathyTable->setMainTabLabel("Препараты");

    connect(ui->homeopathyTable, SIGNAL(onAddButtonClicked()),
            this, SLOT(onAddButtonClicked()));
    connect(ui->homeopathyTable, SIGNAL(onEditButtonClicked(const QVariant&)),
            this, SLOT(onEditButtonClicked(const QVariant&)));
    connect(ui->homeopathyTable, SIGNAL(onTableDoubleClicked(const QVariant&)),
            this, SLOT(onEditButtonClicked(const QVariant&)));
    connect(ui->homeopathyTable, SIGNAL(onDeleteButtonClicked(const QVariant&)),
            this, SLOT(onDeleteButtonClicked(const QVariant&)));
}

void HomeopathyDrugListForm::fillHomeopathyTable(const std::vector<homeopathy::Drug>& homeopathyList) {
    for (const auto& drug : homeopathyList)
        addHomeopathyDrug(drug);
}
