#include "medicineDrugForm.h"
#include "ui_medicineDrugForm.h"

#include <QMessageBox>
#include <QValidator>
#include <QDebug>

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

void MedicineDrugForm::on_buttonBox_accepted() {
    if (!isValid()) {
        showWarning();
        return;
    }

    medicine::Drug currentDrug(ui->activeSubstance->text(),
                               ui->activeSubstanceLat->text(),
                               ui->prescription->isChecked(),
                               releaseForms_,
                               brands_,
                               dosages_,
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
}

void MedicineDrugForm::setWidgetsSettings() {
    setDoubleValidator(ui->price);
}

bool MedicineDrugForm::isValid() {
    bool validFilling  = true;

    if (ui->activeSubstance->text().isEmpty() ||
        (ui->prescription->isChecked() &&
        ui->activeSubstanceLat->text().isEmpty()))
        validFilling = false;
    return validFilling;
}

void MedicineDrugForm::showWarning() {
    QString openModeStr = openMode_ == OpenMode::CREATE ? "добавления" : "редактированя";
    QString warning;

    if (ui->activeSubstance->text().isEmpty())
        warning += "Не задано название активного вещества\n";
    if (ui->prescription->isChecked() &&
        ui->activeSubstanceLat->text().isEmpty())
        warning += "Не задано название активного вещества (лат.)\n";

    QMessageBox::critical(this, "Ошибка " + openModeStr + " лекарства",
                           warning,
                           QMessageBox::Ok);
}

void setDoubleValidator(QLineEdit* lineEdit) {
    QRegExp regExp("[0-9]*[.]?[0-9]*");
    QRegExpValidator* regExpValidator = new QRegExpValidator(regExp);
    lineEdit->setValidator(regExpValidator);
}
