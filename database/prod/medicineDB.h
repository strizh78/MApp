#pragma once

#include "itemProdInterface.h"

#include "drugs/medicines.h"

class MedicineDB : public ItemDBProdInterface<medicine::Drug> {
public:
    MedicineDB();
    friend class AppointmentDB;

private:
    medicine::Drug rowToItem(const QSqlQuery& row, int startPos = 0) override;
    ValueByColumn valuesToUpsert(const medicine::Drug& item) override;
};
