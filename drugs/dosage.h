#pragma once

#include <QString>
#include <QMetaType>

const int DOSAGE_AGE_NO_VALUE = -1;

class Dosage {
public:
    Dosage(int fromInMonths, int toInMonths, const QString& dosage);
    Dosage(const QString& dosage);
    Dosage();
    bool operator != (const Dosage& other);

    QString toString() const;
    static Dosage parseDosage(const QString& dosage);
    bool isParsed() const;
    bool isValid() const;
public:
    int fromInMonths;
    int toInMonths;
    QString dosage;
private:
    QString ageToString(int age) const;
private:
    bool isParsed_;
};

Q_DECLARE_METATYPE(const Dosage*);
