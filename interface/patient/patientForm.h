#pragma once

#include "patient/patient.h"
#include "appointment/appointment.h"
#include "database/databaseInterface.h"

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class PatientForm;
}

class PatientForm : public QWidget {
    Q_OBJECT

public:
    PatientForm(DatabasePtr database,
                std::optional<Patient> patient = std::nullopt,
                QWidget *parent = nullptr);
    ~PatientForm();

signals:
    void patientCreateSignal(const Patient& created);
    void patientEditSignal(const Patient& editedPatient);

private slots:
    void fieldEdited();

    void on_saveInfoBox_accepted();
    void on_saveInfoBox_rejected();

    void on_dateEdit_userDateChanged(const QDate& date);

    void on_addAppointmentBtn_clicked();

    void addAppointment(const Appointment& appointment);

private:
    void setupUi();

    void fillFormPatientInfo();
    void setupAppointmentsInfo();

    Patient buildPatientFromFormData();
    bool trySavePatient();

private:
    Ui::PatientForm *ui;
    std::shared_ptr<QStandardItemModel> infoViewModel_;

    Patient patient_;
    DatabasePtr database_;

    bool isModified;

    friend class PatientTests;
    void setupFilesInfo();
};
