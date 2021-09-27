#pragma once

#include "appointment/appointment.h"

#include "database/databaseInterface.h"

#include <QStandardItem>
#include <QWidget>

namespace Ui {
class AppointmentsListForm;
}

class AppointmentsListForm : public QWidget {
    Q_OBJECT

public:
    explicit AppointmentsListForm(DatabasePtr database,
                                 QWidget *parent = nullptr);
    ~AppointmentsListForm();

private slots:
    void onAddButtonClicked();
    void onEditButtonClicked(const QVariant &data);
    void onDeleteButtonClicked(const QVariant &data);

    void addAppointment(const Appointment& appointment);
    void editAppointment(const Appointment& editedAppointment);

private:
    void setupTableSettings();
    void fillAppointmentsTable(const std::vector<Appointment>& appointmentsList);

private:
    Ui::AppointmentsListForm *ui;
    DatabasePtr database_;
};
