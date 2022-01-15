#include "dosageForm.h"
#include "ui_dosageForm.h"

#include "interface/interfaceUtils.h"

DosageForm::DosageForm(const Dosage& dosage, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DosageForm)
    , dosage_(dosage)
{
    ui->setupUi(this);
    ui->errorLabel->hide();
    initModels();

    setAge(dosage.fromInMonths, "From");
    setAge(dosage.toInMonths, "To");
    ui->shortDosage->setText(dosage.dosage);
    ui->fullDosage->setText(dosage.toString());
    ui->tabWidget->setCurrentIndex(!dosage.isParsed());
}

DosageForm::~DosageForm() {
    delete ui;
}

void DosageForm::on_ageFromSpinBox_valueChanged(int value) {
    spinBoxValueChanged(value, ui->ageFromComboBox);
}

void DosageForm::on_ageToSpinBox_valueChanged(int value) {
    spinBoxValueChanged(value, ui->ageToComboBox);
}

void DosageForm::on_ageFromCheckBox_stateChanged(int state) {
    ui->ageFromSpinBox->setEnabled(state);
    ui->ageFromComboBox->setEnabled(state);
}

void DosageForm::on_ageToCheckBox_stateChanged(int state) {
    ui->ageToSpinBox->setEnabled(state);
    ui->ageToComboBox->setEnabled(state);
}

void DosageForm::on_buttonBox_accepted() {
    if (ui->tabWidget->currentIndex() == 0) {
        dosage_ = Dosage(getAge("From"),
                         getAge("To"),
                         ui->shortDosage->toPlainText());
    }
    else {
        dosage_ = Dosage(ui->fullDosage->toPlainText());
    }
    if (!dosage_.isValid()) {
        ErrorLog::showItemFormWarning(
            ui->errorLabel,
            "Значение \"От\" должно быть меньше \"До\"");
        return;
    }
    emit dosageEditSignal(dosage_);
    close();
}

void DosageForm::on_buttonBox_rejected() {
    close();
}

void DosageForm::initModels() {
    initModel(0, "месяца", "года");
    initModel(1, "месяцев", "лет");
}

void DosageForm::initModel(int idx,
                           const QString& monthStr,
                           const QString& yearStr) {
    QStandardItem* month = new QStandardItem(monthStr);
    month->setData(1, Qt::UserRole);
    QStandardItem* year = new QStandardItem(yearStr);
    year->setData(12, Qt::UserRole);
    model_[idx] = new QStandardItemModel();
    model_[idx]->appendRow(month);
    model_[idx]->appendRow(year);
}

void DosageForm::spinBoxValueChanged(int value, QComboBox* comboBox) {
    setComboModel(value, comboBox);
    comboBox->setDisabled(value >= 12);

    if (value >= 12) {
        comboBox->setCurrentIndex(1);
    }
}

void DosageForm::setComboModel(int value, QComboBox* comboBox) {
    comboBox->setModel(value % 10 == 1 &&
                       value != 11 ? model_[0] : model_[1]);
}

int DosageForm::getAge(const QString& end) {
    QCheckBox* check = ui->dosageTab[0].findChild<QCheckBox*>(
                           QString("age%1CheckBox").arg(end));
    QSpinBox* spin = ui->dosageTab[0].findChild<QSpinBox*>(
                         QString("age%1SpinBox").arg(end));
    QComboBox* combo = ui->dosageTab[0].findChild<QComboBox*>(
                           QString("age%1ComboBox").arg(end));

    if (!check->isChecked()) {
        return DOSAGE_AGE_NO_VALUE;
    }
    return  spin->value() * combo->currentData().value<int>();
}

void DosageForm::setAge(int ageInMonths, const QString& end) {
    QCheckBox* check = ui->dosageTab[0].findChild<QCheckBox*>(QString("age%1CheckBox").arg(end));
    QSpinBox* spin = ui->dosageTab[0].findChild<QSpinBox*>(QString("age%1SpinBox").arg(end));
    QComboBox* combo = ui->dosageTab[0].findChild<QComboBox*>(QString("age%1ComboBox").arg(end));

    auto [age, sufIdx] = parseAge(ageInMonths);
    if (age == DOSAGE_AGE_NO_VALUE) {
        check->setChecked(false);
        return;
    }
    spin->setValue(age);
    setComboModel(age, combo);
    combo->setCurrentIndex(sufIdx);
}

std::pair<int, int> DosageForm::parseAge(int ageInMonths) {
    if (ageInMonths < 12) {
        return {ageInMonths, 0};
    }
    return {ageInMonths / 12, 1};
}
