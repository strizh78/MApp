#include "patientDB.h"

PatientDB::PatientDB() {
    tableName_ = "patients";
    columns_ = {"id"};
    for (const auto& item: valuesToUpsert(Patient())) {
        columns_.push_back(item.first);
    }
}

Patient PatientDB::rowToItem(const QSqlQuery& row, int startPos) {
    Patient result;

    setCode(result, row.value(startPos + 0).toInt());
    setDeleted(result, row.value(startPos + 1).toBool());
    result.nameInfo.name = row.value(startPos + 2).toString();
    result.nameInfo.surname = row.value(startPos + 3).toString();
    result.nameInfo.patronymic = row.value(startPos + 4).toString();
    result.nameInfo.initials = row.value(startPos + 5).toString();
    result.birthDate = row.value(startPos + 6).toDate();
    result.address = split(row.value(startPos + 7).toString(), MULTIPLE_VALUE_SEPARATOR);
    result.phones = split(row.value(startPos + 8).toString(), MULTIPLE_VALUE_SEPARATOR);
    result.emails = split(row.value(startPos + 9).toString(), MULTIPLE_VALUE_SEPARATOR);
    result.additionalInfo = row.value(startPos + 10).toString();
    return result;
}

ValueByColumn PatientDB::valuesToUpsert(const Patient& item) {
    return {
        {"isDeleted", QVariant(item.isDeleted())},
        {"name", QVariant(item.nameInfo.name)},
        {"surname", QVariant(item.nameInfo.surname)},
        {"patronymic", QVariant(item.nameInfo.patronymic)},
        {"initials", QVariant(item.nameInfo.initials)},
        {"birthDate", QVariant(item.birthDate)},
        {"address", QVariant(toString(item.address, MULTIPLE_VALUE_SEPARATOR))},
        {"phones", QVariant(toString(item.phones, MULTIPLE_VALUE_SEPARATOR))},
        {"emails", QVariant(toString(item.emails, MULTIPLE_VALUE_SEPARATOR))},
        {"additionalInfo", QVariant(item.additionalInfo)},
    };
}
