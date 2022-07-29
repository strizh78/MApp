#pragma once

#include "database/itemDatabaseInterface.h"

#include "appointmentDB.h"

#include "file/file.h"
#include "appointment/appointment.h"

#include "QSqlQuery"

class FileDB : public ItemDBInterface<File> {
public:
    FileDB(AppointmentDB* appointmentDb);

    void list(std::vector<File>& receiver) override;
    void add(File& file, int parentCode) override;
    void update(const File& editedItem) override;
    void filesByAppointment(const Appointment& appointment, std::vector<File>& receiver) override;
    void filesByPatient(const Patient& patient, std::vector<File>& receiver) override;
    void appointmentByFile(const File& file, Appointment& appointment) override;

    void link(const File& file, const Appointment& appointment);
    void unlink(const File& file, const Appointment& appointment);

private:
    File rowToItem(const QSqlQuery& row, int startPos = 0);
    ValueByColumn valuesToUpsert(const File& item);
    void handleListResult(QSqlQuery& query, std::vector<File>& receiver);

private:
    QString tableName_;
    std::vector<QString> columns_;
    AppointmentDB* appointmentDb_;
    const QString appoinmentFilesTable_ = "appointment_files";
};
