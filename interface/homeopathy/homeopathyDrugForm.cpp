#include "homeopathyDrugForm.h"
#include "ui_homeopathyDrugForm.h"
#include "homeopathyDrugDilutionsSelectForm.h"

#include "interface/utils.h"

using namespace homeopathy;

HomeopathyDrugForm::HomeopathyDrugForm(std::shared_ptr<DatabaseInterface> database,
                                       std::optional<Drug> drug,
                                       QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::HomeopathyDrugForm)
    , database_(database)
    , drug_(drug.value_or(Drug()))
    , openMode_(drug.has_value() ? OpenMode::EDIT : OpenMode::CREATE)
{
    ui->setupUi(this);
    init();
    ui->errorLabel->setHidden(true);
    Validators::setEnglishValidator(ui->nameLat);
}

HomeopathyDrugForm::~HomeopathyDrugForm() {
    delete ui;
}

void HomeopathyDrugForm::on_addDilutionsBtn_clicked() {
    auto* homeopathyDrugDilutionsSelectForm = new HomeopathyDrugDilutionsSelectForm(dilutions_,
                                                                                    this);
    connect(homeopathyDrugDilutionsSelectForm,
            SIGNAL(dilutionsSelectedSignal(const std::vector<QString>&)),
            this,
            SLOT(fillLabelFromVector(const std::vector<QString>&)));
    homeopathyDrugDilutionsSelectForm->setAttribute(Qt::WA_DeleteOnClose, true);
    homeopathyDrugDilutionsSelectForm->show();
}

void HomeopathyDrugForm::on_buttonBox_accepted() {
    auto invalidFields = isValid();

    if (invalidFields.has_value()) {
        ErrorLog::showItemFormWarning(ui->errorLabel, invalidFields.value());
        return;
    }
    Drug currentDrug(ui->name->text(),
                     ui->nameLat->text(),
                     ui->groupComboBox->currentData().value<Groups>(),
                     dilutions_);
    switch (openMode_) {
        case OpenMode::CREATE:
            database_->addHomeopathyDrug(currentDrug);
            emit homeopathyDrugCreateSignal(currentDrug);
            break;
        case OpenMode::EDIT:
            database_->editHomeopathyDrug(drug_, currentDrug);
            emit homeopathyDrugEditSignal(drug_, currentDrug);
            break;
    }
    close();
}

void HomeopathyDrugForm::on_buttonBox_rejected() {
    close();
}

void HomeopathyDrugForm::fillLabelFromVector(const std::vector<QString>& data) {
    ui->dilutions->setText(toString(data, ", "));
    dilutions_ = data;
}

std::optional<std::vector<QString> > HomeopathyDrugForm::isValid() {
    std::vector<QString> invalidFields;

    if (ui->name->text().isEmpty() &&
        ui->nameLat->text().isEmpty())
    {
        invalidFields.push_back(ui->nameLabel->text());
    }

    if (invalidFields.empty())
        return std::nullopt;
    return invalidFields;
}

void HomeopathyDrugForm::init() {
    setGroupValues();
    switch (openMode_) {
        case OpenMode::CREATE:
            setWindowTitle("Добавление препарата");
            break;
        case OpenMode::EDIT:
            setWindowTitle(drug_.getFullName());
            ui->name->setText(drug_.name());
            ui->nameLat->setText(drug_.nameLat());
            ui->groupComboBox->setCurrentIndex(int(drug_.group()));
            break;
    }
    fillLabelFromVector(drug_.availableDilutions());
}

void HomeopathyDrugForm::setGroupValues() {
    QList<QStandardItem*> list;

    for (int i = 0; i < int(Groups::NUMBER_OF_GROUPS); ++i) {
        auto* item = new QStandardItem(i);
        Groups group = static_cast<Groups>(i);
        item->setData(QVariant::fromValue(group), Qt::UserRole);
        item->setText(groupToString(group));
        list << item;
    }
    groupsModel_ = std::make_shared<QStandardItemModel>();
    groupsModel_->appendColumn(list);
    ui->groupComboBox->setModel(groupsModel_.get());
}
