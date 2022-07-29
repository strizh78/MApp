#pragma once

#include "database/itemDatabaseInterface.h"
#include "file/file.h"

class FilesDBTest : public ItemDBInterface<File> {
public:
    FilesDBTest(ItemDBInterface<Appointment>* appointment);

    void filesByAppointment(const Appointment& appointment, std::vector<File>& receiver) override;
    void filesByPatient(const Patient& patient, std::vector<File>& receiver) override;
    void appointmentByFile(const File& file, Appointment& receiver) override;
    void add(File& file, int parentCode) override;
    void update(const File& editedFile) override;
    void list(std::vector<File>& receiver) override;

protected:
    static std::vector<File> list_;
    static std::vector<int> parentAppointmentCode_;
    static std::vector<Appointment> appointments;
    static int code_;

private:
    int nextCode();
};
