#pragma once

#include <QDate>
#include <QHash>
#include <QString>
#include <QVariant>

class Patient
{
public:
    Patient() = default;
    Patient(const QString& fullName, QDate birthDate, const QString& address);

    QString fullName() const;
    void setFullName(const QString& fullName);

    QDate birthDate() const;
    void setBirthDate(QDate birthDate);

    QString address() const;
    void setAddress(const QString& address);

    const QHash<QString, QVariant>& additionalInfo() const;
    void setAdditionalInfo(const QHash<QString, QVariant>& info);
    void addAdditionalInfo(const QString& key, const QVariant& value);

private:
    QString fullName_;
    QDate birthDate_;
    QString address_;
    QHash<QString, QVariant> additionalInfo_;
};
