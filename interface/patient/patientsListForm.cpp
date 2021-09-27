#include "patientsListForm.h"
#include "ui_patientsListForm.h"
#include "patientForm.h"

#include "interface/utils.h"

PatientsListForm::PatientsListForm(DatabasePtr database,
                         QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientsListForm)
    , database_(database)
{
    ui->setupUi(this);

    std::vector<Patient> patientsList;
    database_->patient->list(patientsList);
    setupTableSettings();
    fillPatientsTable(patientsList);
}

PatientsListForm::~PatientsListForm() {
    delete ui;
}

void PatientsListForm::onAddButtonClicked() {
    auto* patientCreateForm = new PatientForm(database_);
    connect(patientCreateForm, SIGNAL(patientCreateSignal(const Patient&)),
            this, SLOT(addPatient(const Patient&)));

    patientCreateForm->setAttribute(Qt::WA_DeleteOnClose, true);
    patientCreateForm->show();
}

void PatientsListForm::onEditButtonClicked(const QVariant& data) {
    auto* patientViewForm = new PatientForm(database_, *getValueFromModelData<Patient>(data));

    connect(patientViewForm, SIGNAL(patientEditSignal(const Patient&)),
            this, SLOT(editPatient(const Patient&)));

    patientViewForm->setAttribute(Qt::WA_DeleteOnClose, true);
    patientViewForm->show();
}

void PatientsListForm::onDeleteButtonClicked(const QVariant& data) {
    auto value = *getValueFromModelData<Patient>(data);
    database_->patient->setDeletedMark(value, !value.isDeleted());
    editPatient(value);
}

void PatientsListForm::addPatient(const Patient& patient) {
    ui->patientTable->appendRow(patient, CreateRows::createPatientRow(patient));
}

void PatientsListForm::editPatient(const Patient& editedPatient) {
    ui->patientTable->editData(editedPatient, CreateRows::createPatientRow(editedPatient));
}

void PatientsListForm::setupTableSettings() {
    ui->patientTable->setHorizontalHeaderLabels({"Фамилия И.О.", "Дата рождения", "Телефон", "Почта", "Адрес"});
    ui->patientTable->setScale({1, 1, 1, 1, 2});
    ui->patientTable->setMainTabLabel("Пациенты");

    connect(ui->patientTable, SIGNAL(onAddButtonClicked()),
            this, SLOT(onAddButtonClicked()));
    connect(ui->patientTable, SIGNAL(onEditButtonClicked(const QVariant&)),
            this, SLOT(onEditButtonClicked(const QVariant&)));
    connect(ui->patientTable, SIGNAL(onTableDoubleClicked(const QVariant&)),
            this, SLOT(onEditButtonClicked(const QVariant&)));
    connect(ui->patientTable, SIGNAL(onDeleteButtonClicked(const QVariant&)),
            this, SLOT(onDeleteButtonClicked(const QVariant&)));
}

void PatientsListForm::fillPatientsTable(const std::vector<Patient>& patientsList) {
    for (const auto& patient : patientsList) {
        addPatient(patient);
    }
}
