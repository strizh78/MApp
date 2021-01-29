#include "patient.h"

QString Patient::NameInfo::getFullName() const {
    return surname + ' ' + name + ' ' + patronymic;
}

QString Patient::NameInfo::getInitials() const {
    QString initials = surname + ' ' + name[0] + '.';
    if (!patronymic.isEmpty()) {
        initials += patronymic[0] + '.';
    }
    return initials;
}

Patient::Patient(const NameInfo& nameInfo, QDate birthDate, const QString& address)
    : nameInfo_(nameInfo)
    , birthDate_(birthDate)
    , address_(address)
{
}

Patient::NameInfo Patient::nameInfo() const {
    return nameInfo_;
}

void Patient::setNameInfo(const NameInfo& nameInfo) {
    nameInfo_ = nameInfo;
}

QDate Patient::birthDate() const {
    return birthDate_;
}

void Patient::setBirthDate(QDate birthDate) {
    birthDate_ = birthDate;
}

QString Patient::address() const {
    return address_;
}

void Patient::setAddress(const QString& address) {
    address_ = address;
}

const QHash<QString, QString>& Patient::additionalInfo() const {
    return additionalInfo_;
}

void Patient::setAdditionalInfo(const QHash<QString, QString>& info) {
    additionalInfo_ = info;
}

void Patient::addAdditionalInfo(const QString& key, const QString& value) {
    additionalInfo_[key] = value;
}

bool Patient::operator==(const Patient& other) const {
    bool baseFields =  birthDate_ == other.birthDate() &&
                       nameInfo_.getFullName() == other.nameInfo().getFullName() &&
                       address_ == other.address() &&
                       additionalInfo_ == other.additionalInfo();
    if (baseFields == true) {
        baseFields = additionalInfo_.size() == other.additionalInfo().size();
        auto keys = additionalInfo_.keys();
        for (auto& key : keys) {
            if (!other.additionalInfo().contains(key)) {
                baseFields = false;
                break;
            }
        }
    }
    return baseFields;
}

bool Patient::isValid() const {
    if (nameInfo_.name.size() == 0 ||
        nameInfo_.surname.size() == 0)
    {
        return false;
    }

    if (address_.size() == 0) {
        return false;
    }

    if (birthDate_ > QDate::currentDate()) {
        return false;
    }

    return true;
}
