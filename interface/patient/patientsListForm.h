#pragma once

#include "patient/patient.h"
#include "interface/basicForms/mappTable.h"

#include "database/databaseinterface.h"

#include <QStandardItemModel>
#include <QWidget>

#include <memory>
#include <vector>

namespace Ui {
    class PatientsListForm;
}

class PatientsListForm : public QWidget
{
    Q_OBJECT
public:
    explicit PatientsListForm(std::shared_ptr<DatabaseInterface> database,
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
    QList<QStandardItem*> createPatientRow(const Patient& patient);

private:
    Ui::PatientsListForm *ui;
    std::shared_ptr<DatabaseInterface> database_;
    friend class PatientTests;
};
