#include "fileDB.h"

#include "query.h"

FileDB::FileDB(AppointmentDB* appointmentDb) {
    appointmentDb_ = appointmentDb;
    tableName_ = "files";
    columns_ = {"id"};
    for (const auto& item: valuesToUpsert(File(), FileData())) {
        columns_.push_back(item.first);
    }
    columns_.pop_back();
}

void FileDB::list(std::vector<File>& receiver) {
    SelectQuery query(tableName_, columns_);

    if (query.exec()) {
        handleListResult(query, receiver);
    }
}

void FileDB::add(File& file, FileData& data, int parentCode) {
    InsertQuery query(tableName_, valuesToUpsert(file, data));

    if (!query.exec() || !query.first()) {
        return;
    }

    int code = query.value(0).toInt();

    if (code == 0) {
        qCritical() << "Failed to read inserted ID";
        return;
    }

    setCode(file, code);

    InsertQuery(appoinmentFilesTable_, {
        {"file", QVariant(file.code())},
        {"appointment", QVariant(parentCode)}
    }).exec();
};

void FileDB::update(const File& editedFile, const FileData& data) {
    UpdateQuery query(tableName_, valuesToUpsert(editedFile, data));

    query.addWhereStatement("id", SQL_OPERATORS::EQ, editedFile.code());
    query.exec();
};

void  FileDB::filesByAppointment(const Appointment& appointment, std::vector<File>& receiver) {
    SelectQuery innerQuery(appoinmentFilesTable_, {"file"});
    innerQuery.addWhereStatement("appointment", SQL_OPERATORS::EQ, appointment.code());

    SelectQuery query(tableName_, columns_);
    query.addWhereStatement("id", SQL_OPERATORS::IN, innerQuery);

    if (query.exec()) {
        handleListResult(query, receiver);
    }
};

void FileDB::filesByPatient(const Patient& patient, std::vector<File>& receiver) {
    SelectQuery appointmentByPatient(appointmentDb_->tableName_, {"id"});
    appointmentByPatient.addWhereStatement("patient", SQL_OPERATORS::EQ, patient.code());

    SelectQuery fileByAppointment(appoinmentFilesTable_, {"file"});
    fileByAppointment.addWhereStatement(
        "appointment", SQL_OPERATORS::IN, appointmentByPatient
    );

    SelectQuery query(tableName_, columns_);
    query.addWhereStatement("id", SQL_OPERATORS::IN, fileByAppointment);

    if (query.exec()) {
        handleListResult(query, receiver);
    }
};

void FileDB::appointmentByFile(const File& file, Appointment& appointment) {
    SelectQuery fileInnerQuery(appoinmentFilesTable_, {"appointment"});
    fileInnerQuery.addWhereStatement("file", SQL_OPERATORS::EQ, file.code());

    SelectQuery query(appointmentDb_->tableName_, appointmentDb_->columns_);
    query.addWhereStatement("id", SQL_OPERATORS::IN, fileInnerQuery);

    if (query.exec()) {
        appointment = appointmentDb_->rowToItem(query);
    }
}

void FileDB::fileData(const File& file, FileData& data) {
    SelectQuery query(tableName_, {"data"});
    query.addWhereStatement("id", SQL_OPERATORS::EQ, file.code());

    if (query.exec() && query.first()) {
        data = query.value(0).toByteArray();
    }
}

void FileDB::link(const File& file, const Appointment& appointment) {
    InsertQuery(appoinmentFilesTable_, {
        {"file", QVariant(file.code())},
        {"appointment", QVariant(appointment.code())}
    }).exec();
}

void FileDB::unlink(const File& file, const Appointment& appointment) {
    DeleteQuery deleteQuery(appoinmentFilesTable_);
    deleteQuery.addWhereStatement(
        "file", SQL_OPERATORS::EQ, file.code()
    );
    deleteQuery.addWhereStatement(
        "appointment", SQL_OPERATORS::EQ, appointment.code()
    );
    deleteQuery.exec();
}

File FileDB::rowToItem(const QSqlQuery& row, int startPos) {
    File result;

    setCode(result, row.value(startPos + 0).toInt());
    setDeletedMark(result, row.value(startPos + 1).toBool());
    result.name = row.value(startPos + 2).toString();
    result.extension = row.value(startPos + 3).toString();
    result.uploadTime = row.value(startPos + 4).toDateTime();
    result.lastEditTime = row.value(startPos + 5).toDateTime();

    return result;
}

ValueByColumn FileDB::valuesToUpsert(const File& item, const FileData& data) {
    return {
        {"isDeleted", QVariant(item.isDeleted())},
        {"name", QVariant(item.name)},
        {"extension", QVariant(item.extension)},
        {"uploadTime", QVariant(item.uploadTime)},
        {"lastEditTime", QVariant(item.lastEditTime)},
        {"data", QVariant(data)}
    };
}

void FileDB::handleListResult(QSqlQuery& query, std::vector<File>& receiver) {
    while (query.next()) {
        receiver.push_back(rowToItem(query));
    }
}

