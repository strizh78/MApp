#include "homeopathyDrugForm.h"
#include "ui_homeopathyDrugForm.h"
#include "homeopathyDrugDilutionsSelectForm.h"

#include "interface/utils.h"

using namespace homeopathy;

HomeopathyDrugForm::HomeopathyDrugForm(DatabasePtr database,
                                       std::optional<Drug> drug,
                                       QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::HomeopathyDrugForm)
    , database_(database)
    , drug_(drug.value_or(Drug()))
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

    drug_.name = ui->name->text();
    drug_.nameLat = ui->nameLat->text();
    drug_.group = ui->groupComboBox->currentData().value<Groups>();
    drug_.availableDilutions = dilutions_;

    if (drug_.isExists()) {
        database_->homeopathy->update(drug_);
        emit homeopathyDrugEditSignal(drug_);
    } else {
        database_->homeopathy->add(drug_);
        emit homeopathyDrugCreateSignal(drug_);
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

    if (drug_.isExists()) {
        setWindowTitle(drug_.getFullName());
        ui->name->setText(drug_.name);
        ui->nameLat->setText(drug_.nameLat);
        ui->groupComboBox->setCurrentIndex(int(drug_.group));
    } else {
        setWindowTitle("Добавление препарата");
    }

    fillLabelFromVector(drug_.availableDilutions);
}

void HomeopathyDrugForm::setEditEnabled(bool enabled) {
    ui->addDilutionsBtn->setEnabled(enabled);
    ui->groupComboBox->setEnabled(enabled);
    ui->dilutions->setEnabled(enabled);
    ui->name->setEnabled(enabled);
    ui->nameLat->setEnabled(enabled);

    ui->buttonBox->clear();
    if (!enabled) {
        ui->buttonBox->addButton(QDialogButtonBox::Close);
    } else {
        ui->buttonBox->addButton(QDialogButtonBox::Cancel);
        ui->buttonBox->addButton(QDialogButtonBox::Save);
    }

    adjustSize();
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
