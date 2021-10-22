#pragma once

#include "MAppBaseObj/mappBaseObj.h"

#include <QDate>
#include <QHash>
#include <QString>
#include <QVariant>

class Patient : public MAppBaseObj {
public:
    struct NameInfo {
        NameInfo() = default;
        NameInfo(const QString& name, const QString& surname, const QString& patronymic);
        NameInfo(const QString& fullName);

        QString getFullName() const;
        QString getInitials() const;

        QString name;
        QString surname;
        QString patronymic;
        QString initials;

        private:
            void updateInitials();
    };

    Patient() = default;
    Patient(const NameInfo& nameInfo, QDate birthDate);

    bool isValid() const;

public:
    NameInfo nameInfo;
    QDate birthDate;
    std::vector<QString> address;
    std::vector<QString> phones;
    std::vector<QString> emails;
    QString additionalInfo;
};

Q_DECLARE_METATYPE( Patient ); // for QVariant
