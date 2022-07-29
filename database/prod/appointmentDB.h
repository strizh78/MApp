#pragma once

#include "itemProdInterface.h"

#include "medicineDB.h"
#include "homeopathyDB.h"
#include "serviceDB.h"
#include "patientDB.h"

#include "appointment/appointment.h"
#include "drugs/medicines.h"
#include "drugs/homeopathy.h"
#include "service/service.h"
#include "patient/patient.h"

class AppointmentDB : public ItemDBProdInterface<Appointment> {
public:
    AppointmentDB(
            HomeopathyDB* homeopathy,
            MedicineDB* medicine,
            ServiceDB* service,
            PatientDB* patient
    );
    void list(std::vector<Appointment>& receiver) override;
    friend class FileDB;

private:
    void handleListResult(QSqlQuery& query, std::vector<Appointment>& receiver) override;
    Appointment rowToItem(const QSqlQuery& row, int startPos = 0) override;
    ValueByColumn valuesToUpsert(const Appointment& item) override;
    ColumnsWithTable allColumns();

private:
    ItemDBProdInterface<homeopathy::Drug>* homeopathyDb_;
    ItemDBProdInterface<medicine::Drug>* medicineDb_;
    ItemDBProdInterface<Service>* serviceDb_;
    ItemDBProdInterface<Patient>* patientDb_;
};
