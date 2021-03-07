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

    NameInfo nameInfo() const;
    void setNameInfo(const NameInfo& nameInfo);

    QDate birthDate() const;
    void setBirthDate(QDate birthDate);

    QString address() const;
    void setAddress(const QString& address);

    const QHash<QString, QString>& additionalInfo() const;
    void setAdditionalInfo(const QHash<QString, QString>& info);
    void addAdditionalInfo(const QString& key, const QString& value);

    bool isValid() const;

private:
    NameInfo nameInfo_;
    QDate birthDate_;
    QString address_;
    QHash<QString, QString> additionalInfo_;
};

Q_DECLARE_METATYPE( Patient ); // for QVariant
