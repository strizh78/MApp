#pragma once

#include "file/file.h"

#include <memory>

template <class BaseItem>
class ItemDBInterface {
public:
    ItemDBInterface() = default;
    virtual ~ItemDBInterface() = default;

    virtual int nextCode() = 0;

    void setCode(BaseItem& item) {
        item.setCode(nextCode());
    }

    void setDeletedMark(BaseItem& item, bool isDeleted) {
        item.setDeleted(isDeleted);
        update(item);
    }

    virtual void list(std::vector<BaseItem>& ) = 0;
    virtual void add(BaseItem& item) = 0;
    virtual void update(const BaseItem& editedItem) = 0;
};

class Patient;
class Appointment;

template<>
class ItemDBInterface<File> {
public:
    ItemDBInterface() = default;
    virtual ~ItemDBInterface() = default;

    virtual int nextCode() = 0;
    virtual void setCode(File& item) final {
        item.setCode(nextCode());
    }

    virtual void setDeletedMark(File& item, bool isDeleted) final {
        item.setDeleted(isDeleted);
    }

    virtual void list(std::vector<File>& ) = 0;
    virtual void add(File& item, FileData&, int) = 0;
    virtual void update(const File& editedFile, const FileData&) = 0;
    virtual void fileData(const File&, FileData&) = 0;
    virtual void appointmentByFile(const File&, Appointment&) = 0;
    virtual void filesByPatient(const Patient&, std::vector<File>&) = 0;
    virtual void filesByAppointment(const Appointment&, std::vector<File>&) = 0;
};
