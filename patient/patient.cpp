#include "patient.h"

Patient::NameInfo::NameInfo(const QString& name,
                            const QString& surname,
                            const QString& patronymic)
    : name(name)
    , surname(surname)
    , patronymic(patronymic)
{
    updateInitials();
}

Patient::NameInfo::NameInfo(const QString& fullName) {
    auto splittedName = fullName.split(' ');

    surname = (splittedName.size() >= 1) ? splittedName[0] : "";
    name = (splittedName.size() >= 2) ? splittedName[1] : "";
    patronymic = (splittedName.size() >= 3) ? splittedName[2] : "";

    updateInitials();
}

QString Patient::NameInfo::getFullName() const {
    return surname + ' ' + name + ' ' + patronymic;
}

QString Patient::NameInfo::getInitials() const {
    return initials;
}

void Patient::NameInfo::updateInitials() {
    if (surname.isEmpty() || name.isEmpty()) {
        initials = "";
        return;
    }

    initials = surname + ' ' + name[0] + ".";
    if (!patronymic.isEmpty()) {
        initials += patronymic[0] + ".";
    }
}

Patient::Patient(const NameInfo& nameInfo, QDate birthDate)
    : nameInfo(nameInfo)
    , birthDate(birthDate)
{
}

bool Patient::isValid() const {
    if (nameInfo.name.isEmpty() ||
        nameInfo.surname.isEmpty())
    {
        return false;
    }

    if (birthDate > QDate::currentDate()) {
        return false;
    }

    return true;
}
