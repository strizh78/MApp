#include "medicineDB.h"

MedicineDB::MedicineDB() {
    tableName_ = "medicines";
    columns_ = {"id"};
    for (const auto& item: valuesToUpsert(medicine::Drug())) {
        columns_.push_back(item.first);
    }
}

medicine::Drug MedicineDB::rowToItem(const QSqlQuery& row, int startPos) {
    medicine::Drug result;

    setCode(result, row.value(startPos + 0).toInt());
    setDeleted(result, row.value(startPos + 1).toBool());

    result.name = row.value(startPos + 2).toString();
    result.activeSubstance = row.value(startPos + 3).toString();
    result.activeSubstanceLat = row.value(startPos + 4).toString();
    result.isPrescription = row.value(startPos + 5).toBool();
    result.contraindications = row.value(startPos + 6).toString();
    result.price = row.value(startPos + 7).toFloat();
    result.releaseForms = split(row.value(startPos + 8).toString(), MULTIPLE_VALUE_SEPARATOR);

    for (const auto& dosage: split(row.value(startPos + 9).toString(), MULTIPLE_VALUE_SEPARATOR)) {
        result.dosages.push_back(Dosage(dosage));
    }
    result.brandNames = split(row.value(startPos + 10).toString(), MULTIPLE_VALUE_SEPARATOR);

    return result;
}

ValueByColumn MedicineDB::valuesToUpsert(const medicine::Drug& item) {
    std::vector<QString> dosages;

    for (const auto& dosage: item.dosages) {
        dosages.push_back(dosage.toString());
    }

    return {
        {"isDeleted", QVariant(item.isDeleted())},
        {"name", QVariant(item.name)},
        {"activeSubstance", QVariant(item.activeSubstance)},
        {"activeSubstanceLat", QVariant(item.activeSubstanceLat)},
        {"isPrescription", QVariant(item.isPrescription)},
        {"contraindications", QVariant(item.contraindications)},
        {"price", QVariant(item.price)},
        {"releaseForms", QVariant(
            toString(item.releaseForms, MULTIPLE_VALUE_SEPARATOR)
        )},
        {"dosages", QVariant(
            toString(dosages, MULTIPLE_VALUE_SEPARATOR)
        )},
        {"brands", QVariant(
            toString(item.brandNames, MULTIPLE_VALUE_SEPARATOR)
        )}
    };
}
