#include "eventDB.h"

EventDB::EventDB() {
    tableName_ = "events";
    columns_ = {"id"};
    for (const auto& item: valuesToUpsert(Event())) {
        columns_.push_back(item.first);
    }
}

Event EventDB::rowToItem(const QSqlQuery& row, int startPos) {
    Event result;

    setCode(result, row.value(startPos + 0).toInt());
    setDeleted(result, row.value(startPos + 1).toBool());
    result.title = row.value(startPos + 2).toString();
    result.dateTime = row.value(startPos + 3).toDateTime();
    result.duration = row.value(startPos + 4).toTime();
    result.comment = row.value(startPos + 5).toString();
    return result;
}

ValueByColumn EventDB::valuesToUpsert(const Event& item) {
    return {
        {"isDeleted", QVariant(item.isDeleted())},
        {"title", QVariant(item.title)},
        {"date", QVariant(item.dateTime)},
        {"duration", QVariant(item.duration)},
        {"comment", QVariant(item.comment)}
    };
}
