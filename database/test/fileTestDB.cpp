#include "fileTestDB.h"
#include "appointment/appointment.h"

#include <QFileInfoList>

#include <algorithm>

std::vector<File> FilesDBTest::list_ = {};
std::vector<QByteArray> FilesDBTest::dataList_ = {};
std::vector<int> FilesDBTest::parentAppointmentCode_ = {};
std::vector<Appointment> FilesDBTest::appointments = {};
int FilesDBTest::code_ = 0;

namespace  {
QByteArray getFileBytes(const QString& fileName) {
    QByteArray bytes;
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly)) {
        bytes = file.readAll();
        file.close();
    }
    return bytes;
}
}

FilesDBTest::FilesDBTest(ItemDBInterface<Appointment>* appointment) {
    struct FullFileData {
        File file;
        FileData data;
        int parentCode;

        FullFileData(File _file, FileData _data, int _parentCode)
            : file(_file)
            , data(_data)
            , parentCode (_parentCode)
        {}
    };

    appointment->list(appointments);
    int parentCode = appointments[0].code();
    QString longString;

    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 100; ++j)
            longString.push_back('a' + j % 26);
        longString.push_back('\n');
    }

    std::vector<FullFileData> fullList = {
        FullFileData(File("Справка", "txt"),
                     QString("Пациент здоров, The patient is healthy").toLocal8Bit(), parentCode),
        FullFileData(File("Заключение", "txt"), longString.toLocal8Bit(), parentCode),
        FullFileData(File("Рентген", "png"), getFileBytes(":/icons/trash.png"), parentCode),
        FullFileData(File("Рецепт из братска от 2017", "jpeg"),
                     getFileBytes(":/test_files/test_jpeg_image.jpeg"), parentCode)
    };

    for (auto& item : fullList) {
        add(item.file, item.data, item.parentCode);
    }
}

int FilesDBTest::nextCode() {
    return ++code_;
}

void FilesDBTest::list(std::vector<File>& receiver) {
    receiver = list_;
}

void FilesDBTest::add(File& file, FileData& data, int parentCode) {
    setCode(file);
    list_.push_back(file);
    dataList_.push_back(data);
    parentAppointmentCode_.push_back(parentCode);
}

void FilesDBTest::edit(const File& oldFile, File& newFile, const FileData& data) {
    auto it = std::find(list_.begin(), list_.end(), oldFile);
    if (it == list_.end()) {
        return;
    }

    int idx = it - list_.begin();
    setCodeToEdit(newFile, oldFile.code());
    list_[idx] = newFile;
    dataList_[idx] = data;
}

void FilesDBTest::fileData(const File& file, FileData& data) {
    auto it = std::find(list_.begin(), list_.end(), file);
    if (it != list_.end()) {
        data = dataList_[it - list_.begin()];
    }
}

void FilesDBTest::appointmentByFile(const File& file, Appointment& receiver) {
    auto it = std::find(list_.begin(), list_.end(), file);
    if (it != list_.end()) {
        int code = parentAppointmentCode_[it - list_.begin()];

        for (auto app : appointments) {
            if (app.code() != code)
                continue;
            receiver = app;
            break;
        }
    }
}

void FilesDBTest::filesByPatient(const Patient& patient, std::vector<File>& receiver) {
    for (const Appointment& appointment : appointments)
        if (appointment.patient == patient)
            filesByAppointment(appointment, receiver);
}

void FilesDBTest::filesByAppointment(const Appointment& appointment, std::vector<File>& receiver) {
    int parentCode = appointment.code();
    for (int i = 0; i < list_.size(); ++i)
        if (parentAppointmentCode_[i] == parentCode)
            receiver.push_back(list_[i]);
}
