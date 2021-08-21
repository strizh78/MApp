#include "appointmentForm.h"
#include "ui_appointmentForm.h"

#include "interface/patient/patientForm.h"
#include "interface/service/serviceForm.h"
#include "interface/homeopathy/homeopathyDrugForm.h"
#include "interface/file/filesListForm.h"

#include "interface/basicForms/mappTable.h"

#include "interface/utils.h"

namespace {
std::vector<QString> getInvalidFields(const Appointment& appointment, bool isNewAppointment) {
    std::vector<QString> wrongFields;
    if (!appointment.patient.isExists()) {
        wrongFields.push_back("Пациент");
    }

    if (!appointment.service.isExists()) {
        wrongFields.push_back("Услуга");
    }

    QDateTime past10Mins = QDateTime::currentDateTime().addSecs(/*seconds*/ -10 * 60);
    if (isNewAppointment && appointment.date < past10Mins) {
        wrongFields.push_back("Дата");
    }
    return wrongFields;
}

template <class T>
QString getDrugsInfoString(const std::vector<T>& drugs) {
    std::vector<QString> drugsNames;
    for (const auto& x : drugs) {
        drugsNames.push_back(x.getFullName());
    }
    return toString(drugsNames);
}
}

AppointmentForm::AppointmentForm(std::shared_ptr<DatabaseInterface> database,
                                 OpenMode mode,
                                 std::optional<Appointment> appointment,
                                 QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AppointmentForm)
    , database_(database)
    , openMode_(mode)
    , currentAppointment_(appointment.value_or(Appointment()))
{
    ui->setupUi(this);
    ui->errorLabel->setVisible(false);

    switch (openMode_) {
        case OpenMode::CREATE:
            setupCreateUi();
            break;
        case OpenMode::EDIT:
            setupEditUi();
    }
    fillAppointmentInfo();
    ui->fileTable->setupDatabase(database_);
    ui->fileTable->fillTable(currentAppointment_);
}

AppointmentForm::~AppointmentForm() {
    delete ui;
}

void AppointmentForm::on_solutionBox_accepted() {
    currentAppointment_.record = ui->appointmentRecord->getText();

    auto wrongFields = getInvalidFields(currentAppointment_, openMode_ == OpenMode::CREATE);
    if (!wrongFields.empty()) {
        ErrorLog::showItemFormWarning(ui->errorLabel, wrongFields);
        return;
    }

    switch (openMode_) {
    case OpenMode::CREATE:
        database_->addAppointment(currentAppointment_);
        emit appointmentCreateSignal(currentAppointment_);
        break;
    case OpenMode::EDIT:
        database_->editAppointment(currentAppointment_);
        emit appointmentEditSignal(currentAppointment_);
        break;
    }
    close();
}

void AppointmentForm::on_solutionBox_rejected() {
    close();
}

void AppointmentForm::on_patientChooseBtn_clicked() {
    auto* selectionForm = createSelectionForm(this);

    std::vector<Patient> patientsList;
    database_->patients(patientsList);
    for (const auto& x : patientsList) {
        selectionForm->appendRow(x, CreateRows::createPatientRow(x));
    }

    connect(selectionForm, SIGNAL(onChooseButtonClicked(QVariant)),
            this, SLOT(patientChoosed(QVariant)));
    connect(selectionForm, SIGNAL(onTableDoubleClicked(QVariant)),
            this, SLOT(patientChoosed(QVariant)));

    selectionForm->show();
    selectionForm->setItemSelected(currentAppointment_.patient);
}

void AppointmentForm::on_serviceChooseBtn_clicked() {
    auto* selectionForm = createSelectionForm(this);

    std::vector<Service> servicesList;
    database_->services(servicesList);
    for (const auto& x : servicesList) {
        selectionForm->appendRow(x, CreateRows::createServiceRow(x));
    }

    connect(selectionForm, SIGNAL(onChooseButtonClicked(QVariant)),
            this, SLOT(serviceChoosed(QVariant)));
    connect(selectionForm, SIGNAL(onTableDoubleClicked(QVariant)),
            this, SLOT(serviceChoosed(QVariant)));

    selectionForm->show();
    selectionForm->setItemSelected(currentAppointment_.service);
}

void AppointmentForm::on_homeopathyChooseBtn_clicked() {
    auto* selectionForm = createSelectionForm(this);

    std::vector<homeopathy::Drug> homeopathyList;
    database_->homeopathyDrugs(homeopathyList);
    for (const auto& x : homeopathyList) {
        selectionForm->appendRow(x, CreateRows::createHomeopathyDrugRow(x));
    }

    connect(selectionForm, SIGNAL(onChooseButtonClicked(QVariant)),
            this, SLOT(homeopathyChoosed(QVariant)));
    connect(selectionForm, SIGNAL(onTableDoubleClicked(QVariant)),
            this, SLOT(homeopathyChoosed(QVariant)));

    selectionForm->show();
    selectionForm->setItemSelected(currentAppointment_.homeopathy);
}

void AppointmentForm::on_addMedicinesBtn_clicked() {
    auto* selectionForm = createSelectionForm(this);

    std::vector<medicine::Drug> medicinesList;
    database_->medicineDrugs(medicinesList);
    for (const auto& x : medicinesList) {
        selectionForm->appendRow(x, CreateRows::createMedicineDrugRow(x));
    }

    connect(selectionForm, SIGNAL(onChooseButtonClicked(std::vector<QVariant>)),
            this, SLOT(medicineChoosed(std::vector<QVariant>)));

    selectionForm->show();

    selectionForm->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);
    for (const auto& x : currentAppointment_.medicines) {
        selectionForm->setItemSelected(x);
    }
}

void AppointmentForm::on_dateEdit_dateChanged(const QDate &date) {
    currentAppointment_.date.setDate(date);
}

void AppointmentForm::on_timeEdit_timeChanged(const QTime &time) {
    currentAppointment_.date.setTime(time);
}

void AppointmentForm::on_patientViewBtn_clicked() {
    auto* patientViewForm = new PatientForm(database_, currentAppointment_.patient, this);
    showAsWindowModal(patientViewForm);
}

void AppointmentForm::on_serviceViewBtn_clicked() {
    auto* serviceViewForm = new ServiceForm(database_, currentAppointment_.service,
                                            ServiceForm::OpenMode::VIEW, this);
    showAsWindowModal(serviceViewForm);
}

void AppointmentForm::on_homeopathyViewBtn_clicked() {
    auto* homeopathyViewForm = new HomeopathyDrugForm(database_, currentAppointment_.homeopathy,
                                                      HomeopathyDrugForm::OpenMode::VIEW, this);
    showAsWindowModal(homeopathyViewForm);
}

void AppointmentForm::on_openRecordBtn_clicked(bool checked) {
    hideRecording(!checked);
}

void AppointmentForm::on_copyAppointmentBtn_clicked() {
    Appointment copied;
    copied.patient = currentAppointment_.patient;
    copied.service = currentAppointment_.service;

    auto* appointmentViewForm =
        new AppointmentForm(database_, AppointmentForm::CREATE, copied, this);

    appointmentViewForm->setWindowModality(Qt::WindowModality::WindowModal);
    appointmentViewForm->setWindowFlag(Qt::Window);
    appointmentViewForm->setAttribute(Qt::WA_DeleteOnClose, true);
    appointmentViewForm->show();
}

void AppointmentForm::patientChoosed(QVariant data) {
    currentAppointment_.patient = *getValueFromModelData<Patient>(data);
    ui->patientEdit->setText(currentAppointment_.patient.nameInfo.getInitials());
    ((QWidget*)sender())->close();
}

void AppointmentForm::serviceChoosed(QVariant data) {
    currentAppointment_.service = *getValueFromModelData<Service>(data);
    ui->serviceEdit->setText(currentAppointment_.service.name);
    ((QWidget*)sender())->close();
}

void AppointmentForm::homeopathyChoosed(QVariant data) {
    currentAppointment_.homeopathy = *getValueFromModelData<homeopathy::Drug>(data);
    ui->homeopathyEdit->setText(currentAppointment_.homeopathy.getFullName());

    ((QWidget*)sender())->close();
}

void AppointmentForm::medicineChoosed(std::vector<QVariant> data) {
    currentAppointment_.medicines.clear();
    for (const auto& medicine : data) {
        currentAppointment_.medicines.push_back(*getValueFromModelData<medicine::Drug>(medicine));
    }
    ui->medicinesList->setText(getDrugsInfoString(currentAppointment_.medicines));

    ((QWidget*)sender())->close();
}

void AppointmentForm::setupCreateUi() {
    setWindowTitle("Создание приёма");
    hideDrugs();
    hideRecording(true);

    ui->openRecordBtn->setChecked(false);
    ui->copyAppointmentBtn->setHidden(true);
}

void AppointmentForm::setupEditUi() {
    setWindowTitle("Приём " + currentAppointment_.date.toString("d MMMM yyyy, h:mm"));
    ui->appointmentRecord->setEditEnabled(false);
}

void AppointmentForm::hideDrugs() {
    ui->drugs->setHidden(true);
    adjustSize();
}

void AppointmentForm::hideRecording(bool hide) {
    ui->designLine->setHidden(hide);
    ui->appointmentRecord->setHidden(hide);
    adjustSize();
}

void AppointmentForm::fillAppointmentInfo() {
    if (currentAppointment_.patient.isExists()) {
        ui->patientEdit->setText(currentAppointment_.patient.nameInfo.getInitials());
    }
    if (currentAppointment_.service.isExists()) {
        ui->serviceEdit->setText(currentAppointment_.service.name);
    }
    if (currentAppointment_.homeopathy.isExists()) {
        ui->homeopathyEdit->setText(currentAppointment_.homeopathy.getFullName());
    }

    ui->dateEdit->setDate(currentAppointment_.date.date());
    ui->timeEdit->setTime(currentAppointment_.date.time());

    ui->medicinesList->setText(getDrugsInfoString(currentAppointment_.medicines));

    ui->appointmentRecord->setText(currentAppointment_.record);
}
