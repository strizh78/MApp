#include "appointmentDB.h"

#include <QString>

AppointmentDB::AppointmentDB(
    HomeopathyDB* homeopathy,
    MedicineDB* medicine,
    ServiceDB* service,
    PatientDB* patient)
    : homeopathyDb_(homeopathy)
    , medicineDb_(medicine)
    , serviceDb_(service)
    , patientDb_(patient)
{
    tableName_ = "appointments";

    columns_ = {
        "id", "isDeleted", "date", "isConducted",
        "homeopathy", "service", "patient"
    };
}

void AppointmentDB::list(std::vector<Appointment>& receiver) {
    SelectQuery query(tableName_, allColumns());
    query.leftJoin(homeopathyDb_->getTableName(), "id", "homeopathy");
    query.leftJoin(serviceDb_->getTableName(), "id", "service");
    query.leftJoin(patientDb_->getTableName(), "id", "patient");
    query.leftJoin("prescribed_medications", "appointment", "id");
    query.leftJoin(medicineDb_->getTableName(), "id", "prescribed_medications", "medicine");

    if (query.exec()) {
        handleListResult(query, receiver);
    }
}

void AppointmentDB::handleListResult(QSqlQuery& query, std::vector<Appointment>& receiver) {
    auto pushIfNotEmpty = [&](const Appointment& appointment) {
        if (appointment != Appointment()) {
            receiver.push_back(appointment);
        }
    };
    Appointment current;

    while (query.next()) {
        Appointment next = rowToItem(query);

        if (next == current) {
            current.medicines.push_back(next.medicines[0]);
            continue;
        }

        pushIfNotEmpty(current);
        current = next;
    }
    pushIfNotEmpty(current);
}

Appointment AppointmentDB::rowToItem(const QSqlQuery& row, int startPos) {
    Appointment result;
    int columnsShift = columns_.size();

    setCode(result, row.value(startPos + 0).toInt());
    setDeleted(result, row.value(startPos + 1).toBool());
    result.date = row.value(startPos + 2).toDateTime();
    result.isConducted = row.value(startPos + 3).toBool();

    result.homeopathy = homeopathyDb_->rowToItem(row, columnsShift);
    columnsShift += homeopathyDb_->getColumns().size();

    result.service = serviceDb_->rowToItem(row, columnsShift);
    columnsShift +=  serviceDb_->getColumns().size();

    result.patient = patientDb_->rowToItem(row, columnsShift);
    columnsShift +=  patientDb_->getColumns().size();

    result.medicines.push_back(medicineDb_->rowToItem(row, columnsShift));

    return result;
}

ValueByColumn AppointmentDB::valuesToUpsert(const Appointment& item) {
    ValueByColumn result = {
        {"id", QVariant(item.code())},
        {"isDeleted", QVariant(item.isDeleted())},
        {"date", QVariant(item.date)},
        {"isConducted", QVariant(item.isConducted)},
    };
    auto addCodeIfExists = [&](const QString& column, int code) {
        if (code) {
            result.push_back({column, code});
        }
    };
    addCodeIfExists("homeopathy", item.homeopathy.code());
    addCodeIfExists("service", item.service.code());
    addCodeIfExists("patient", item.patient.code());

    return result;
}

ColumnsWithTable AppointmentDB::allColumns() {
    ColumnsWithTable columnsWithTable;

    auto insertColumns = [&](const std::vector<QString>& source, const QString& table) {
        for (const auto& column : source) {
            columnsWithTable.push_back({table, column});
        }
    };

    insertColumns(columns_, tableName_);
    insertColumns(homeopathyDb_->getColumns(), homeopathyDb_->getTableName());
    insertColumns(serviceDb_->getColumns(), serviceDb_->getTableName());
    insertColumns(patientDb_->getColumns(), patientDb_->getTableName());
    insertColumns(medicineDb_->getColumns(), medicineDb_->getTableName());

    return columnsWithTable;
}
