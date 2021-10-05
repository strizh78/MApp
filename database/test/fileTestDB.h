#pragma once

#include "database/itemDatabaseInterface.h"
#include "file/file.h"

class FilesDBTest : public ItemDBInterface<File> {
public:
    FilesDBTest(ItemDBInterface<Appointment>* appointment);

    void filesByAppointment(const Appointment& appointment, std::vector<File>& receiver) override;
    void filesByPatient(const Patient& patient, std::vector<File>& receiver) override;
    void appointmentByFile(const File& file, Appointment& urr) override;
    void fileData(const File& file, FileData& data) override;
    void add(File& file, FileData& data, int parentCode) override;
    void update(const File& editedFile, const FileData& data) override;
    void list(std::vector<File>& receiver) override;

    int nextCode() override;

protected:
    static std::vector<File> list_;
    static std::vector<QByteArray> dataList_;
    static std::vector<int> parentAppointmentCode_;
    static std::vector<Appointment> appointments;
    static int code_;
};
