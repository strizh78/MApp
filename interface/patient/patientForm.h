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
    PatientForm(std::shared_ptr<DatabaseInterface> database,
                std::optional<Patient> patient = std::nullopt,
                QWidget *parent = nullptr);
    ~PatientForm();

signals:
    void patientCreateSignal(const Patient& created);
    void patientEditSignal(const Patient& editedPatient);

private slots:
    void addPatientInfo(const QString& key, const QString& value);

    void on_solutionBox_accepted();
    void on_solutionBox_rejected();

    void on_createInfo_clicked();
    void on_deleteInfo_clicked();
    void on_editInfo_clicked();

    void on_dateEdit_userDateChanged(const QDate& date);

private:
    void setupUi();
    void setupInfoTable();
    void enableTableButtons(bool enabled);

    void fillFormPatientInfo();
    Patient buildPatientFromFormData();

private:
    enum class OpenMode {
        CREATE,
        EDIT
    };

private:
    Ui::PatientForm *ui;
    std::shared_ptr<QStandardItemModel> infoViewModel_;

    Patient patient_;
    OpenMode openMode_;
    std::shared_ptr<DatabaseInterface> database_;

    friend class PatientTests;
};
