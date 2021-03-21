#include "appointmentsListForm.h"
#include "ui_appointmentsListForm.h"

#include "appointmentForm.h"

#include "interface/utils.h"

AppointmentsListForm::AppointmentsListForm(std::shared_ptr<DatabaseInterface> database,
                                           QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AppointmentsListForm)
    , database_(database)
{
    ui->setupUi(this);
    setupTableSettings();

    std::vector<Appointment> appointmentsList;
    database_->appointments(appointmentsList);
    fillAppointmentsTable(appointmentsList);
}

AppointmentsListForm::~AppointmentsListForm() {
    delete ui;
}

void AppointmentsListForm::onAddButtonClicked() {
    auto* appointmentCreateForm = new AppointmentForm(database_, AppointmentForm::CREATE);
    connect(appointmentCreateForm, SIGNAL(appointmentCreateSignal(const Appointment&)),
            this, SLOT(addAppointment(const Appointment&)));

    appointmentCreateForm->setAttribute(Qt::WA_DeleteOnClose, true);
    appointmentCreateForm->show();
}

void AppointmentsListForm::onEditButtonClicked(const QVariant& data) {
    auto* appointmentViewForm = new AppointmentForm(database_, AppointmentForm::EDIT,
                                                    *getValueFromModelData<Appointment>(data));

    connect(appointmentViewForm, SIGNAL(appointmentEditSignal(const Appointment&)),
            this, SLOT(editAppointment(const Appointment&)));

    appointmentViewForm->setAttribute(Qt::WA_DeleteOnClose, true);
    appointmentViewForm->show();
}

void AppointmentsListForm::onDeleteButtonClicked(const QVariant& data) {
    auto value = *getValueFromModelData<Appointment>(data);
    database_->setDeletedMark(value, !value.isDeleted());
    editAppointment(value);
}

void AppointmentsListForm::addAppointment(const Appointment& appointment) {
    ui->appointmentTable->appendRow(appointment, createAppointmentRow(appointment));
}

void AppointmentsListForm::editAppointment(const Appointment& editedAppointment) {
    ui->appointmentTable->editData(editedAppointment, createAppointmentRow(editedAppointment));
}

void AppointmentsListForm::setupTableSettings() {
    ui->appointmentTable->setHorizontalHeaderLabels({"Пациент", "Услуга", "Дата/время приёма"});
    ui->appointmentTable->setMainTabLabel("Приёмы");

    connect(ui->appointmentTable, SIGNAL(onAddButtonClicked()),
            this, SLOT(onAddButtonClicked()));
    connect(ui->appointmentTable, SIGNAL(onEditButtonClicked(const QVariant&)),
            this, SLOT(onEditButtonClicked(const QVariant&)));
    connect(ui->appointmentTable, SIGNAL(onTableDoubleClicked(const QVariant&)),
            this, SLOT(onEditButtonClicked(const QVariant&)));
    connect(ui->appointmentTable, SIGNAL(onDeleteButtonClicked(const QVariant&)),
            this, SLOT(onDeleteButtonClicked(const QVariant&)));
}

void AppointmentsListForm::fillAppointmentsTable(const std::vector<Appointment>& appointmentsList) {
    for (const auto& appointment : appointmentsList) {
        addAppointment(appointment);
    }
}

QList<QStandardItem*> AppointmentsListForm::createAppointmentRow(const Appointment& appointment) {
    QList<QStandardItem*> lst;

    QStandardItem* patientName = new QStandardItem(appointment.patient.nameInfo().getInitials());
    patientName->setData(getModelData(appointment), Qt::UserRole);

    QStandardItem* serviceName = new QStandardItem(appointment.service.name());
    QStandardItem* dateTime = new QStandardItem(appointment.date.toString("d MMMM yyyy, h:mm"));

    lst << patientName << serviceName << dateTime;
    return lst;
}
