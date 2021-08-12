#pragma once

#include "patient/patient.h"
#include "database/databaseinterface.h"

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class PatientForm;
}

class PatientForm : public QWidget {
    Q_OBJECT

public:
    enum class OpenMode {
        CREATE,
        EDIT,
        VIEW
    };

public:
    PatientForm(std::shared_ptr<DatabaseInterface> database,
                std::optional<Patient> patient = std::nullopt,
                OpenMode mode = OpenMode::CREATE,
                QWidget *parent = nullptr);
    ~PatientForm();

signals:
    void patientCreateSignal(const Patient& created);
    void patientEditSignal(const Patient& editedPatient);

private slots:
    void fieldEdited();

    void on_solutionBox_accepted();
    void on_solutionBox_rejected();

    void on_dateEdit_userDateChanged(const QDate& date);

    void on_addAppointmentBtn_clicked();

    void addAppointment(const Appointment& appointment);

private:
    void setupUi();
    void setEditEnabled(bool enabled);

    void fillFormPatientInfo();
    void setupAppointmentsInfo();

    Patient buildPatientFromFormData();
    bool trySavePatient();

private:
    Ui::PatientForm *ui;
    std::shared_ptr<QStandardItemModel> infoViewModel_;

    Patient patient_;
    OpenMode openMode_;
    std::shared_ptr<DatabaseInterface> database_;

    bool isModified;

    friend class PatientTests;
};
