#include "medicineDrugForm.h"
#include "ui_medicineDrugForm.h"

#include "medicineDrugReleaseFormSelectForm.h"
#include "medicineDrugBrandSelectForm.h"
#include "interface/utils.h"

#include "interface/utils.h"

#include <QMessageBox>
#include <QValidator>

MedicineDrugForm::MedicineDrugForm(std::shared_ptr<DatabaseInterface> database,
                                   std::optional<medicine::Drug> drug,
                                   QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::MedicineDrugForm)
    , database_(database)
    , drug_(drug.value_or(medicine::Drug()))
    , openMode_(drug.has_value() ? OpenMode::EDIT : OpenMode::CREATE)
{
    ui->setupUi(this);
    init();
    setWidgetsSettings();
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
    addDosage();
    ui->dosages->selectRow(ui->dosages->model()->rowCount() - 1);
    ui->dosages->edit(dosagesModel_->index(dosagesModel_->rowCount() - 1, 0));
}

void MedicineDrugForm::on_deleteDosageBtn_clicked() {
    int curRow = ui->dosages->currentIndex().row();
    dosagesModel_->removeRow(curRow);
    ui->dosages->selectRow(std::min(dosagesModel_->rowCount() - 1, curRow));
    ui->dosages->setFocus();
}

void MedicineDrugForm::on_editDosageBtn_clicked() {
    ui->dosages->edit(ui->dosages->currentIndex());
}

void MedicineDrugForm::on_buttonBox_accepted() {
    auto invalidFields = isValid();
    if (invalidFields.has_value()) {
        ErrorLog::showItemFormWarning(ui->errorLabel, invalidFields.value());
        return;
    }

    medicine::Drug currentDrug(ui->activeSubstance->text(),
                               ui->activeSubstanceLat->text(),
                               ui->prescription->isChecked(),
                               releaseForms_,
                               brands_,
                               getDosages(),
                               ui->price->text().toFloat());
    switch (openMode_) {
        case OpenMode::CREATE:
            database_->addMedicineDrug(currentDrug);
            emit medicineDrugCreateSignal(currentDrug);
            break;
        case OpenMode::EDIT:
            database_->editMedicineDrug(drug_, currentDrug);
            emit medicineDrugEditSignal(drug_, currentDrug);
            break;
    }
    close();
}

void MedicineDrugForm::on_buttonBox_rejected() {
    close();
}

void MedicineDrugForm::fillLabelFromVector(QLabel* label, const std::vector<QString>& data) {
    label->setText(toString(data, ", "));

    if (label == ui->releaseForms)
        releaseForms_ = data;
    if (label == ui->brands)
        brands_ = data;
}

void MedicineDrugForm::init() {
    switch (openMode_) {
        case OpenMode::CREATE:
            setWindowTitle("Добавление лекарства");
            break;
        case OpenMode::EDIT:
            setWindowTitle("Лекарство " + drug_.getFullName());
            ui->activeSubstance->setText(drug_.activeSubstance());
            ui->activeSubstanceLat->setText(drug_.activeSubstancetLat());
            ui->prescription->setChecked(drug_.isPrescription());
            ui->price->setText(QString::number(drug_.price()));
            break;
    }
    fillLabelFromVector(ui->brands, drug_.brandNames());
    fillLabelFromVector(ui->releaseForms, drug_.releaseForms());
    fillDosagesList();
}

void MedicineDrugForm::setWidgetsSettings() {
    Validators::setDoubleValidator(ui->price);
    Validators::setEnglishValidator(ui->activeSubstanceLat);
    ui->errorLabel->setHidden(true);
  
    if (dosagesModel_->rowCount() != 0) {
        ui->dosages->selectRow(0);
    } else {
        ui->deleteDosageBtn->setEnabled(false);
        ui->editDosageBtn->setEnabled(false);
    }
}

std::optional<std::vector<QString>> MedicineDrugForm::isValid() {
    std::vector<QString> invalidFields;

    if (ui->brands->text().isEmpty()) {
        invalidFields.push_back(ui->brandsLabel->text());
    }
    if (ui->prescription->isChecked() &&
        ui->activeSubstance->text().isEmpty())
    {
        invalidFields.push_back(ui->activeSubstanceLatLabel->text());
    }

    if (invalidFields.empty())
        return std::nullopt;
    return invalidFields;
}

void MedicineDrugForm::fillDosagesList() {
    dosagesModel_ = std::make_shared<QStandardItemModel>();

    static const QStringList columnNames = {"Дозировка"};
    dosagesModel_->setHorizontalHeaderLabels(columnNames);

    for (auto& dosage : drug_.dosages())
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

    name->setText(dosage);
    name->setData(QVariant::fromValue(dosage), Qt::UserRole);
    lst << name;

    return lst;
}

std::vector<Dosage> MedicineDrugForm::getDosages() {
    std::vector<Dosage> dosages;

    for (int i = 0; i < dosagesModel_->rowCount(); ++i) {
        auto index = dosagesModel_->index(i, 0);
        dosages.push_back(dosagesModel_->data(index, Qt::UserRole).toString());
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
