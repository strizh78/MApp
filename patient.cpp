#include "patient.h"

Patient::Patient(const QString& fullName, QDate birthDate, const QString& address)
    : fullName_(fullName)
    , birthDate_(birthDate)
    , address_(address)
{
}

QString Patient::fullName() const {
    return fullName_;
}

void Patient::setFullName(const QString& fullName) {
    fullName_ = fullName;
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
