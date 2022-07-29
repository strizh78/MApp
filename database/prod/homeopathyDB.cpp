#include "homeopathyDB.h"

namespace {
homeopathy::Groups stringToGroup(const QString& str) {
    if (str == "Животные") {
        return homeopathy::Groups::ANIMALS;
    }
    if (str == "Неживое") {
        return homeopathy::Groups::IMMATERIAL;
    }
    if (str == "Минералы") {
        return homeopathy::Groups::MINERALS;
    }
    if (str == "Растения") {
        return homeopathy::Groups::PLANTS;
    }
    return homeopathy::Groups::NUMBER_OF_GROUPS;
}
}

HomeopathyDB::HomeopathyDB() {
    tableName_ = "homeopathy";
    columns_ = {"id"};

    for (const auto& item: valuesToUpsert(homeopathy::Drug())) {
        columns_.push_back(item.first);
    }
}

homeopathy::Drug HomeopathyDB::rowToItem(const QSqlQuery& row, int startPos) {
    homeopathy::Drug result;

    setCode(result, row.value(startPos + 0).toInt());
    setDeleted(result, row.value(startPos + 1).toBool());

    result.name = row.value(startPos + 2).toString();
    result.nameLat = row.value(startPos + 3).toString();
    result.group = stringToGroup(row.value(startPos + 4).toString());
    result.availableDilutions = split(row.value(startPos + 5).toString(), MULTIPLE_VALUE_SEPARATOR);

    return result;
}

ValueByColumn HomeopathyDB::valuesToUpsert(const homeopathy::Drug& item) {
    return {
        {"isDeleted", QVariant(item.isDeleted())},
        {"name", QVariant(item.name)},
        {"nameLat", QVariant(item.nameLat)},
        {"group", QVariant(homeopathy::groupToString(item.group))},
        {"dilution", QVariant(
            toString(item.availableDilutions, MULTIPLE_VALUE_SEPARATOR)
        )}
    };
}
