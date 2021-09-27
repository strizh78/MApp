#pragma once

#include "patient/patient.h"
#include "interface/basicForms/mappTable.h"

#include "database/databaseInterface.h"

#include <QStandardItemModel>
#include <QWidget>

#include <memory>
#include <vector>

namespace Ui {
    class PatientsListForm;
}

class PatientsListForm : public QWidget {
    Q_OBJECT
public:
    explicit PatientsListForm(DatabasePtr database,
                         QWidget *parent = nullptr);
    ~PatientsListForm();

private slots:
    void onAddButtonClicked();
    void onEditButtonClicked(const QVariant &data);
    void onDeleteButtonClicked(const QVariant &data);
    void addPatient(const Patient& patient);
    void editPatient(const Patient& editedPatient);

private:
    void setupTableSettings();
    void fillPatientsTable(const std::vector<Patient>& patientsList);

private:
    Ui::PatientsListForm *ui;
    DatabasePtr database_;
    friend class PatientTests;
};
