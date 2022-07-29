#pragma once

#include "itemProdInterface.h"

#include "timetable/event.h"

class EventDB : public ItemDBProdInterface<Event> {
public:
    EventDB();

private:
    Event rowToItem(const QSqlQuery& row, int startPos = 0) override;
    ValueByColumn valuesToUpsert(const Event& item) override;
};
