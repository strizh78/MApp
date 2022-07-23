#pragma once

#include "itemProdInterface.h"

#include "service/service.h"

class ServiceDB : public ItemDBProdInterface<Service> {
public:
    ServiceDB();
    friend class AppointmentDB;

protected:
    Service rowToItem(const QSqlQuery& row, int startPos = 0) override;
    ValueByColumn valuesToUpsert(const Service& item) override;
};
