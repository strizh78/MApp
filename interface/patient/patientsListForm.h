#pragma once

#include "patientForm.h"
#include "interface/tableSettingsForm.h"

#include "patient/patient.h"
#include "database/databaseinterface.h"

#include <QWidget>
#include <QStringList>
#include <QStandardItemModel>

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

    void resizeEvent(QResizeEvent *event) override;

private slots:
    void addPatient(const Patient& patient);
    void editPatient(const Patient& oldPatient, const Patient& editedPatient);

    void on_createPatient_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_tableSettings_clicked();

    void on_searchLine_returnPressed();
    void on_searchLine_textChanged(const QString &text);

private:
    void searchInTable(const QString& searchRequest);

    void showPatientInfo(const Patient& patient);
    void fillPatientsTable(const std::vector<Patient>& patientsList);
    QList<QStandardItem*> createPatientRow(size_t row, const Patient& patient);

private:
    Ui::PatientsListForm *ui;
    std::shared_ptr<DatabaseInterface> database_;

    std::shared_ptr<QStandardItemModel> tableViewModel_;
    friend class PatientTests;
};
