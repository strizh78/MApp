#include "dosage.h"

#include <QStringList>
#include <QRegExp>

#include <optional>

namespace {
QString combineDosageText(QStringList::iterator begin, QStringList::iterator end) {
    QString dosage = "";

    for (auto it = begin; it != end; ++it) {
        dosage.push_back(QString(*it) + ' ');
    }
    dosage.chop(1);

    return dosage;
}

int parseAge(int age, const QString& ageType) {
    if (ageType.toLower().startsWith("мес")) {
        return age;
    }
    return age * 12;
}

std::optional<Dosage> fullParser(const QString& dosage) {
    if (!QRegExp("от \\d+ .{1,7} до \\d+ .{1,7} .+")
        .exactMatch(dosage.toLower()))
    {
        return std::nullopt;
    }
    QStringList words = dosage.split(' ', Qt::SkipEmptyParts);
    return Dosage(
            parseAge(words[1].toInt(), words[2]),
            parseAge(words[4].toInt(), words[5]),
            combineDosageText(words.begin() + 6, words.end()));
}

std::optional<Dosage> fromParser(const QString& dosage) {
    if (!QRegExp("от \\d+ .{1,7} .+")
        .exactMatch(dosage.toLower()))
    {
        return std::nullopt;
    }
    QStringList words = dosage.split(' ', Qt::SkipEmptyParts);
    return Dosage(
            parseAge(words[1].toInt(), words[2]),
            DOSAGE_AGE_NO_VALUE,
            combineDosageText(words.begin() + 3, words.end()));
}

std::optional<Dosage> toParser(const QString& dosage) {
    Dosage parseResult;
    if (!QRegExp("до \\d+ .{1,7} .+")
        .exactMatch(dosage.toLower()))
    {
        return std::nullopt;
    }
    QStringList words = dosage.split(' ', Qt::SkipEmptyParts);
    return Dosage(
            DOSAGE_AGE_NO_VALUE,
            parseAge(words[1].toInt(), words[2]),
            combineDosageText(words.begin() + 3, words.end()));
}
}

Dosage::Dosage(int fromInMonths, int toInMonths, const QString& dosage)
    : fromInMonths(fromInMonths)
    , toInMonths(toInMonths)
    , dosage(dosage)
    , isParsed_(true)
{
}

Dosage::Dosage(const QString& dosage)
    : Dosage(parseDosage(dosage))
{
}

Dosage::Dosage()
    : fromInMonths(DOSAGE_AGE_NO_VALUE)
    , toInMonths(DOSAGE_AGE_NO_VALUE)
    , dosage("")
    , isParsed_(false)
{
}

bool Dosage::operator !=(const Dosage& other) {
    return fromInMonths != other.fromInMonths ||
            toInMonths != other.toInMonths ||
            dosage != other.dosage;
}

QString Dosage::toString() const {
    QString dosageStr;
    if (fromInMonths != DOSAGE_AGE_NO_VALUE) {
        dosageStr.push_back(QString("от %1 ").arg(ageToString(fromInMonths)));
    }
    if (toInMonths != DOSAGE_AGE_NO_VALUE) {
        dosageStr.push_back(QString("до %1 ").arg(ageToString(toInMonths)));
    }
    dosageStr.push_back(QString("%1").arg(dosage));
    return dosageStr;
}

Dosage Dosage::parseDosage(const QString& dosage) {
    std::optional<Dosage> dosageFull = fullParser(dosage);
    if (dosageFull.has_value()) {
        return dosageFull.value();
    }
    std::optional<Dosage> dosageFrom = fromParser(dosage);
    if (dosageFrom.has_value()) {
        return dosageFrom.value();
    }
    std::optional<Dosage> dosageTo = toParser(dosage);
    if (dosageTo.has_value()) {
         return dosageTo.value();
    }
    Dosage notParsed;
    notParsed.dosage = dosage;
    return notParsed;
}

bool Dosage::isParsed() const {
    return isParsed_;
}

bool Dosage::isValid() const {
    if (!isParsed_) {
        return true;
    }
    if (toInMonths == DOSAGE_AGE_NO_VALUE) {
        return true;
    }
    return fromInMonths < toInMonths;
}

QString Dosage::ageToString(int age) const {
    if (age < 12) {
        return QString::number(age) + " мес.";
    }
    if (age == 12) {
        return "1 года";
    }
    return QString::number(age / 12) + " лет";
}
