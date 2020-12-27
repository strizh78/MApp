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

const QHash<QString, QVariant>& Patient::additionalInfo() const {
    return additionalInfo_;
}

void Patient::setAdditionalInfo(const QHash<QString, QVariant>& info) {
    additionalInfo_ = info;
}

void Patient::addAdditionalInfo(const QString& key, const QVariant& value) {
    additionalInfo_[key] = value;
}
