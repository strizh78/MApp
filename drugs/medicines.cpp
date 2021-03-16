#include "medicines.h"

namespace medicine {

Drug::Drug(const QString& activeSubstance,
           const QString& activeSubstanceLat,
           bool isPrescription,
           const std::vector<ReleaseForm>& releaseForms,
           const std::vector<QString>& brandNames,
           const std::vector<QString>& dosages,
           float price)
    : activeSubstance_(activeSubstance)
    , activeSubstancetLat_(activeSubstanceLat)
    , isPrescription_(isPrescription)
    , releaseForms_(releaseForms)
    , brandNames_(brandNames)
    , dosages_(dosages)
    , price_(price)
{
}

QString Drug::activeSubstance() const {
    return activeSubstance_;
}

QString Drug::activeSubstancetLat() const {
    return activeSubstancetLat_;
}

bool Drug::isPrescription() const {
    return isPrescription_;
}

std::vector<ReleaseForm> Drug::releaseForms() const {
    return releaseForms_;
}

std::vector<QString> Drug::brandNames() const {
    return brandNames_;
}

std::vector<Dosage> Drug::dosages() const {
    return dosages_;
}

float Drug::price() const {
    return price_;
}

QString Drug::getFullName() const {
    if (activeSubstance_.isEmpty())
        return  activeSubstancetLat_;

    QString fullName = activeSubstance_;

    if (!activeSubstancetLat_.isEmpty())
        fullName += " (" + activeSubstancetLat_ + ")";

    return fullName;
}

QString Drug::getBrands(QString separator) const {
    QString brands;

    for (const QString &brand : brandNames_)
        brands += brand + separator;
    brands.resize(brands.size() - separator.size());

    return brands;
}
}
