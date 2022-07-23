#include "serviceDB.h"

ServiceDB::ServiceDB() {
    tableName_ = "services";
    columns_ = {"id"};
    for (const auto& item: valuesToUpsert(Service())) {
        columns_.push_back(item.first);
    }
}

Service ServiceDB::rowToItem(const QSqlQuery& row, int startPos) {
    Service result;

    setCode(result, row.value(startPos + 0).toInt());
    setDeleted(result, row.value(startPos + 1).toBool());
    result.name = row.value(startPos + 2).toString(),
    result.price = row.value(startPos + 3).toFloat(),
    result.duration = row.value(startPos + 4).toTime();
    result.isDeprecated = row.value(5 + startPos).toBool();

    return result;
}

ValueByColumn ServiceDB::valuesToUpsert(const Service& item) {
    return {
        {"isDeleted", QVariant(item.isDeleted())},
        {"name", QVariant(item.name)},
        {"price", QVariant(item.price)},
        {"duration", QVariant(item.duration)},
        {"isDeprecated", QVariant(item.isDeprecated)}
    };
}
