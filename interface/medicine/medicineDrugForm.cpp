#include "medicineDrugForm.h"
#include "ui_medicineDrugForm.h"

#include "medicineDrugReleaseFormSelectForm.h"
#include "medicineDrugBrandSelectForm.h"
#include "dosageForm.h"

#include "utils/utils.h"
#include "interface/interfaceUtils.h"

MedicineDrugForm::MedicineDrugForm(DatabasePtr database,
                                   std::optional<medicine::Drug> drug,
                                   QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::MedicineDrugForm)
    , database_(database)
    , drug_(drug.value_or(medicine::Drug()))
{
    ui->setupUi(this);
    init();
    setWidgetsSettings();

    connect(dosagesModel_.get(), SIGNAL(itemChanged(QStandardItem*)),
            this, SLOT(dosageEdit(QStandardItem*)));
}

MedicineDrugForm::~MedicineDrugForm() {
    delete ui;
}

void MedicineDrugForm::on_addBrandsBtn_clicked() {
    auto* medicineDrugBrandSelectForm = new MedicineDrugBrandSelectForm(brands_,
                                                                        ui->brands,
                                                                        this);
    connect(medicineDrugBrandSelectForm,
            SIGNAL(brandsSelectedSignal(QLabel*, const std::vector<QString>&)),
            this,
            SLOT(fillLabelFromVector(QLabel*, const std::vector<QString>&)));
    medicineDrugBrandSelectForm->setAttribute(Qt::WA_DeleteOnClose, true);
    medicineDrugBrandSelectForm->show();
}

void MedicineDrugForm::on_addReleaseFormsBtn_clicked() {
    auto* medicineDrugReleaseFormSelectForm = new MedicineDrugReleaseFormSelectForm(releaseForms_,
                                                                                    ui->releaseForms,
                                                                                    this);
    connect(medicineDrugReleaseFormSelectForm,
            SIGNAL(releaseFormsSelectedSignal(QLabel*, const std::vector<QString>&)),
            this,
            SLOT(fillLabelFromVector(QLabel*, const std::vector<QString>&)));
    medicineDrugReleaseFormSelectForm->setAttribute(Qt::WA_DeleteOnClose, true);
    medicineDrugReleaseFormSelectForm->show();
}

void MedicineDrugForm::on_addDosagesBtn_clicked() {
    addDosage(Dosage());
    int rowCount = dosagesModel_->rowCount();
    ui->dosages->edit(dosagesModel_->index(rowCount - 1, 0));

    if (rowCount == 1) {
        setButtonsEnabled(true);
    }
}

void MedicineDrugForm::on_deleteDosageBtn_clicked() {
    int curRow = ui->dosages->currentIndex().row();
    dosagesModel_->removeRow(curRow);
    int rowCount = dosagesModel_->rowCount();

    if (rowCount != 0) {
        ui->dosages->selectRow(std::min(rowCount - 1, curRow));
        ui->dosages->setFocus();
    }
    else
        setButtonsEnabled(false);
}

void MedicineDrugForm::on_editDosageBtn_clicked() {
    auto data = ui->dosages->currentIndex().data(Qt::UserRole);
    auto* dosageForm = new DosageForm(*data.value<const Dosage*>(), this);
    connect(dosageForm,
            SIGNAL(dosageEditSignal(const Dosage&)),
            this,
            SLOT(dosageEdit(const Dosage&)));
    showAsWindowModal(dosageForm);
}

void MedicineDrugForm::on_buttonBox_accepted() {
    auto invalidFields = isValid();
    if (invalidFields.has_value()) {
        ErrorLog::showItemFormWarning(ui->errorLabel, invalidFields.value());
        return;
    }

    drug_.name = ui->name->text();
    drug_.activeSubstance = ui->activeSubstance->text();
    drug_.activeSubstanceLat = ui->activeSubstanceLat->text();
    drug_.isPrescription = ui->prescription->isChecked();
    drug_.releaseForms = releaseForms_;
    drug_.brandNames = brands_;
    drug_.dosages = getDosages();
    drug_.contraindications = ui->contraindications->toPlainText();
    drug_.price = ui->price->text().toFloat();

    if (drug_.isExists()) {
        database_->medicine->update(drug_);
        emit medicineDrugEditSignal(drug_);
    } else {
        database_->medicine->add(drug_);
        emit medicineDrugCreateSignal(drug_);
    }
    close();
}

void MedicineDrugForm::on_buttonBox_rejected() {
    close();
}

void MedicineDrugForm::fillLabelFromVector(QLabel* label, const std::vector<QString>& data) {
    label->setText(toString(data, ", "));

    if (label == ui->releaseForms) {
        releaseForms_ = data;
    }
    if (label == ui->brands) {
        brands_ = data;
    }
}

void MedicineDrugForm::dosageEdit(const Dosage &dosage) {
    int row = ui->dosages->currentIndex().row();
    auto dosageRow = createDosageRow(row, dosage);
    dosagesModel_->removeRow(row);
    dosagesModel_->insertRow(row, dosageRow);
}

void MedicineDrugForm::dosageEdit(QStandardItem* item) {
    Dosage newDosage = Dosage(item->data(Qt::DisplayRole).toString());
    Dosage curDosage = *(ui->dosages->currentIndex().data(Qt::UserRole)
                           .value<const Dosage*>());
    if (newDosage != curDosage) {
        const Dosage* dosage = new Dosage(newDosage);
        item->setData(QVariant::fromValue(dosage), Qt::UserRole);
    }
}

void MedicineDrugForm::init() {
    if (drug_.isExists()) {
        setWindowTitle("Лекарство " + drug_.getFullName());
        ui->name->setText(drug_.getFullName());
        ui->activeSubstance->setText(drug_.activeSubstance);
        ui->activeSubstanceLat->setText(drug_.activeSubstanceLat);
        ui->prescription->setChecked(drug_.isPrescription);
        ui->contraindications->setText(drug_.contraindications);
        ui->price->setText(QString::number(drug_.price));
    } else {
        setWindowTitle("Добавление лекарства");
    }

    fillLabelFromVector(ui->brands, drug_.brandNames);
    fillLabelFromVector(ui->releaseForms, drug_.releaseForms);
    fillDosagesList();
}

void MedicineDrugForm::setWidgetsSettings() {
    Validators::setDoubleValidator(ui->price);
    Validators::setEnglishValidator(ui->activeSubstanceLat);
    ui->errorLabel->setHidden(true);
  
    if (dosagesModel_->rowCount() != 0) {
        ui->dosages->selectRow(0);
    }
    else
        setButtonsEnabled(false);
}

std::optional<std::vector<QString>> MedicineDrugForm::isValid() {
    std::vector<QString> invalidFields;

    if (ui->brands->text().isEmpty()) {
        invalidFields.push_back(ui->brandsLabel->text());
    }
    if (ui->prescription->isChecked() &&
        ui->activeSubstanceLat->text().isEmpty())
    {
        invalidFields.push_back(ui->activeSubstanceLatLabel->text());
    }

    return invalidFields.empty() ? std::nullopt : std::make_optional(invalidFields);
}

void MedicineDrugForm::fillDosagesList() {
    dosagesModel_ = std::make_shared<QStandardItemModel>();

    static const QStringList columnNames = {"Дозировка"};
    dosagesModel_->setHorizontalHeaderLabels(columnNames);

    for (auto& dosage : drug_.dosages)
        addDosage(dosage);
    ui->dosages->setModel(dosagesModel_.get());
}

void MedicineDrugForm::addDosage(const Dosage& dosage) {
    int rowCount = dosagesModel_->rowCount();
    dosagesModel_->appendRow(createDosageRow(rowCount, dosage));
    ui->dosages->selectRow(rowCount);
  
    ui->deleteDosageBtn->setEnabled(true);
    ui->editDosageBtn->setEnabled(true);
}

QList<QStandardItem*> MedicineDrugForm::createDosageRow(size_t row, const Dosage& dosage) {
    QList<QStandardItem*> lst;
    QStandardItem* name = new QStandardItem(row, 0);

    name->setText(dosage.toString());
    const Dosage* dosagePtr = new Dosage(dosage);
    name->setData(QVariant::fromValue(dosagePtr), Qt::UserRole);
    lst << name;

    return lst;
} 

std::vector<Dosage> MedicineDrugForm::getDosages() {
    std::vector<Dosage> dosages;

    for (int i = 0; i < dosagesModel_->rowCount(); ++i) {
        auto data = dosagesModel_->item(i, 0)->text();

        if (!data.isEmpty()) {
            dosages.push_back(data);
        }
    }
    return dosages;
}

void MedicineDrugForm::resizeEvent(QResizeEvent* event) {
    static const std::vector<int> scale = {1};
    static const int dimension = std::accumulate(scale.begin(), scale.end(), 0);

    for (int column = 0; column < dosagesModel_->columnCount(); ++column) {
        ui->dosages->setColumnWidth(column, ui->dosages->width() * scale[column] / dimension);
    }

    QWidget::resizeEvent(event);
}

void MedicineDrugForm::setButtonsEnabled(bool isEnabled) {
    ui->editDosageBtn->setEnabled(isEnabled);
    ui->deleteDosageBtn->setEnabled(isEnabled);
}
