#pragma once

#include "itemProdInterface.h"

#include "patient/patient.h"

class PatientDB : public ItemDBProdInterface<Patient> {
public:
    PatientDB();
    friend class AppointmentDB;

protected:
    Patient rowToItem(const QSqlQuery& row, int startPos = 0) override;
    ValueByColumn valuesToUpsert(const Patient& item) override;
};
