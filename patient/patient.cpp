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
    : nameInfo(nameInfo)
    , birthDate(birthDate)
    , address(address)
{
}

bool Patient::isValid() const {
    if (nameInfo.name.isEmpty() ||
        nameInfo.surname.isEmpty())
    {
        return false;
    }

    if (address.isEmpty()) {
        return false;
    }

    if (birthDate > QDate::currentDate()) {
        return false;
    }

    return true;
}
