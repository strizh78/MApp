#pragma once

#include "patient/patient.h"
#include "interface/patient/patientForm.h"

#include "database/databaseinterface.h"

#include <QObject>
#include <QTest>
#include <QtTest/QtTest>

class PatientTests : public QObject
{
    Q_OBJECT
public:
    explicit PatientTests(std::shared_ptr<DatabaseInterface> database, QObject *parent = nullptr);
private slots:
    void createPatient();
    void editPatients();

    void patientInfoCreate();

    void listPatients();

private:
    void assertModifyPatient(const Patient& patient, const Patient& edited, bool valid, const std::string& messageWhat);
    void assertCreatePatient(const Patient& patient, bool valid, const std::string& messageWhat);

    void setPatientFormFields(PatientForm& form, const Patient& patient);

    void connectFormsAndAcceptPatientInfo(PatientForm& patientForm, PatientInfoForm& infoForm,
                                          std::pair<QString, QString> additionalInfo);

private:
    std::shared_ptr<DatabaseInterface> database_;
};
