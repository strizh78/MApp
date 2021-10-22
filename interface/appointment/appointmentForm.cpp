#include "appointmentForm.h"
#include "ui_appointmentForm.h"

#include "interface/patient/patientForm.h"
#include "interface/service/serviceForm.h"
#include "interface/homeopathy/homeopathyDrugForm.h"
#include "interface/file/filesListForm.h"

#include "interface/basicForms/mappTable.h"

#include "interface/utils.h"
#include "timetable/timetableUtils.h"

#include <QPainter>
#include <QMessageBox>
#include <QCloseEvent>

namespace {
std::vector<QString> getInvalidFields(const Appointment& appointment, DatabaseInterface* db) {
    std::vector<QString> wrongFields;
    if (!appointment.patient.isExists()) {
        wrongFields.push_back("Пациент");
    }

    if (!appointment.service.isExists()) {
        wrongFields.push_back("Услуга");
    }

    QDateTime past10Mins = QDateTime::currentDateTime().addSecs(/*seconds*/ -10 * 60);
    if (!appointment.isExists() && appointment.date < past10Mins) {
        wrongFields.push_back("Время приёма уже прошло");
    }

    if (!isTimeSlotAvailable(db, appointment, appointment.date, appointment.service.duration)) {
        wrongFields.push_back("Время для приёма уже занято");
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

AppointmentForm::AppointmentForm(DatabasePtr database,
                                 std::optional<Appointment> appointment,
                                 QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AppointmentForm)
    , database_(database)
    , currentAppointment_(appointment.value_or(Appointment()))
{
    ui->setupUi(this);
    ui->conductAppointmentBtn->setVisible(false);
    ui->errorLabel->setVisible(false);

    if (currentAppointment_.isExists()) {
        setupEditUi();
    } else {
        setupCreateUi();
    }

    fillAppointmentInfo();
    ui->fileTable->setupDatabase(database_);
    ui->fileTable->fillTable(currentAppointment_);

    adjustSize();
}

AppointmentForm::~AppointmentForm() {
    delete ui;
}

void AppointmentForm::on_solutionBox_accepted() {
    currentAppointment_.record = ui->appointmentRecord->getHtml();
    currentAppointment_.isConducted |= isHeldNow_;

    auto wrongFields = getInvalidFields(currentAppointment_, database_.get());
    if (!wrongFields.empty()) {
        ErrorLog::showItemFormWarning(ui->errorLabel, wrongFields);
        return;
    }

    if (currentAppointment_.isExists()) {
        database_->appointment->update(currentAppointment_);
        emit appointmentEditSignal(currentAppointment_);
    } else {
        database_->appointment->add(currentAppointment_);
        emit appointmentCreateSignal(currentAppointment_);
    }

    isHeldNow_ = false;
    close();
}

void AppointmentForm::on_solutionBox_rejected() {
    close();
}

template <class T, class CreateRowFunc, class RowChooseSlot>
void AppointmentForm::showSingleSelectionForm(ItemDBInterface<T>* databaseItem, CreateRowFunc createRowFunc,
                                              RowChooseSlot chooseSlot, const T& itemSelected)
{
    auto* selectionForm = createSelectionForm(this);

    std::vector<T> dataList;
    databaseItem->list(dataList);
    for (const auto& x : dataList) {
        selectionForm->appendRow(x, createRowFunc(x));
    }

    connect(selectionForm, SIGNAL(onChooseButtonClicked(QVariant)),
            this, chooseSlot);
    connect(selectionForm, SIGNAL(onTableDoubleClicked(QVariant)),
            this, chooseSlot);

    selectionForm->show();
    selectionForm->setItemSelected(itemSelected);
}

void AppointmentForm::on_patientChooseBtn_clicked() {
    showSingleSelectionForm(database_->patient, CreateRows::createPatientRow,
                            SLOT(patientChoosed(QVariant)), currentAppointment_.patient);
}

void AppointmentForm::on_serviceChooseBtn_clicked() {
    showSingleSelectionForm(database_->service, CreateRows::createServiceRow,
                            SLOT(serviceChoosed(QVariant)), currentAppointment_.service);
}

void AppointmentForm::on_homeopathyChooseBtn_clicked() {
    showSingleSelectionForm(database_->homeopathy, CreateRows::createHomeopathyDrugRow,
                            SLOT(homeopathyChoosed(QVariant)), currentAppointment_.homeopathy);
}

void AppointmentForm::on_addMedicinesBtn_clicked() {
    auto* selectionForm = createSelectionForm(this);

    std::vector<medicine::Drug> medicinesList;
    database_->medicine->list(medicinesList);
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
    setupAppointmentTimeType();
}

void AppointmentForm::on_timeEdit_timeChanged(const QTime &time) {
    currentAppointment_.date.setTime(time);
    setupAppointmentTimeType();
}

void AppointmentForm::on_patientViewBtn_clicked() {
    auto* patientViewForm = new PatientForm(database_, currentAppointment_.patient, this);
    showAsWindowModal(patientViewForm);
}

void AppointmentForm::on_serviceViewBtn_clicked() {
    auto* serviceViewForm = new ServiceForm(database_,
                                            currentAppointment_.service,
                                            this);
    showAsWindowModal(serviceViewForm);
}

void AppointmentForm::on_homeopathyViewBtn_clicked() {
    auto* homeopathyViewForm = new HomeopathyDrugForm(database_,
                                                      currentAppointment_.homeopathy,
                                                      this);
    showAsWindowModal(homeopathyViewForm);
}

void AppointmentForm::on_openRecordBtn_clicked(bool checked) {
    setRecordHidden(checked);
}

void AppointmentForm::on_copyAppointmentBtn_clicked() {
    Appointment copied;
    copied.patient = currentAppointment_.patient;
    copied.service = currentAppointment_.service;

    auto* appointmentViewForm =
        new AppointmentForm(database_, copied, this);

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

    setRecordHidden(true);
    ui->openRecordBtn->hide();

    ui->copyAppointmentBtn->hide();

    ui->statusIcon->hide();
    ui->statusText->hide();
}

void AppointmentForm::setupEditUi() {
    setWindowTitle("Приём " + currentAppointment_.date.toString("d MMMM yyyy, h:mm"));
    setupAppointmentTimeType();
}

void AppointmentForm::setupAppointmentTimeType() {
    if (!currentAppointment_.isExists()) {
        return;
    }

    ui->conductAppointmentBtn->setVisible(currentAppointment_.getTimeType() == Appointment::PRESENT && !currentAppointment_.isConducted);
    setEditFieldsEnabled(!currentAppointment_.isConducted);

    setRecordHidden(false);
    ui->appointmentRecord->setEditEnabled(false);

    if (currentAppointment_.record.isEmpty()) {
        ui->openRecordBtn->setEnabled(false);
        ui->openRecordBtn->setIcon(QIcon(":/icons/noIcon.png"));
        ui->openRecordBtn->setText("Нет записи приёма");
    }

    ui->homeopathyEdit->setEnabled(false);
    ui->homeopathyChooseBtn->setEnabled(false);

    ui->medicinesList->setEnabled(false);
    ui->addMedicinesBtn->setEnabled(false);
    setupStatus();
}

void AppointmentForm::setupStatus() {
    QPixmap pix(20, 20);
    QPainter painter (&pix);

    QColor color = getAppointmentColor(currentAppointment_);
    painter.setPen(color);
    painter.setBrush(color);
    painter.drawRect(pix.rect());

    ui->statusIcon->setPixmap(pix);

    QString status = "";
    switch (currentAppointment_.getTimeType()) {
    case Appointment::PAST:
        status = currentAppointment_.isConducted ? "Приём проведен." : "Время приёма прошло. Приём не был проведён.";
        break;
    case Appointment::PRESENT:
        if (currentAppointment_.isConducted) {
            status = "Приём проведен.";
        } else if (isHeldNow_) {
            status = "Приём проводится.";
        } else{
            status = "Сейчас время приёма. Приём может быть проведён.";
        }
        break;
    case Appointment::FUTURE:
        status = "Приём запланирован.";
        break;
    }
    ui->statusText->setText(status);
}

void AppointmentForm::setEditFieldsEnabled(bool enabled) {
    ui->patientEdit->setEnabled(enabled);
    ui->patientChooseBtn->setEnabled(enabled);

    ui->serviceEdit->setEnabled(enabled);
    ui->serviceChooseBtn->setEnabled(enabled);

    ui->dateEdit->setEnabled(enabled);
    ui->timeEdit->setEnabled(enabled);
}

void AppointmentForm::hideDrugs() {
    ui->drugs->hide();
    adjustSize();
}

void AppointmentForm::setRecordHidden(bool visible) {
    if (!ui->openRecordBtn->isEnabled()) {
        return;
    }

    ui->designLine->setHidden(visible);
    ui->appointmentRecord->setHidden(visible);
    ui->openRecordBtn->setChecked(!visible);
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

    ui->appointmentRecord->setHtml(currentAppointment_.record);
}

void AppointmentForm::on_conductAppointmentBtn_clicked() {
    isHeldNow_ = true;
    setEditFieldsEnabled(false);
    ui->conductAppointmentBtn->hide();

    ui->appointmentRecord->setEditEnabled(true);

    ui->openRecordBtn->setEnabled(true);
    ui->openRecordBtn->setIcon(QIcon(":/icons/transfer.png"));
    ui->openRecordBtn->setText("Открыть запись приёма");
    setRecordHidden(false);

    ui->homeopathyEdit->setEnabled(true);
    ui->homeopathyChooseBtn->setEnabled(true);

    ui->medicinesList->setEnabled(true);
    ui->addMedicinesBtn->setEnabled(true);

    setupStatus();
}

void AppointmentForm::closeEvent(QCloseEvent *event) {
    if (isHeldNow_) {
        auto button = QMessageBox::warning(this, "Сейчас проводится приём!", "Желаете сохранить изменения?",
                                           QDialogButtonBox::StandardButton::Save, QDialogButtonBox::StandardButton::Cancel);
        if (button == QDialogButtonBox::StandardButton::Save) {
            on_solutionBox_accepted();
            return;
        }
    }
    event->accept();
}
