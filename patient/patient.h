#pragma once

#include "MAppBaseObj/mappBaseObj.h"

#include <QDate>
#include <QHash>
#include <QString>
#include <QVariant>

class Patient : public MAppBaseObj {
public:
    struct NameInfo {
        QString getFullName() const;
        QString getInitials() const;

        QString name;
        QString surname;
        QString patronymic;
    };

    Patient() = default;
    Patient(const NameInfo& nameInfo, QDate birthDate, const QString& address);

    bool isValid() const;

public:
    NameInfo nameInfo;
    QDate birthDate;
    QString address;
    QString additionalInfo;
};

Q_DECLARE_METATYPE( Patient ); // for QVariant
