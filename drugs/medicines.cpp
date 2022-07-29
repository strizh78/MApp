#include "medicines.h"

namespace medicine {

Drug::Drug(const QString& name,
           const QString& activeSubstance,
           const QString& activeSubstanceLat,
           bool isPrescription,
           const std::vector<ReleaseForm>& releaseForms,
           const std::vector<QString>& brandNames,
           const std::vector<Dosage>& dosages,
           const QString& contraindications,
           float price)
    : name(name)
    , activeSubstance(activeSubstance)
    , activeSubstanceLat(activeSubstanceLat)
    , isPrescription(isPrescription)
    , releaseForms(releaseForms)
    , brandNames(brandNames)
    , dosages(dosages)
    , contraindications(contraindications)
    , price(price)
{
}

QString Drug::getFullName() const {
    if (name.isEmpty()) {
        return getActiveSubstance();
    }
    return name;
}

QString Drug::getActiveSubstance() const {
    if (activeSubstance.isEmpty()) {
        return  activeSubstanceLat;
    }

    QString fullName = activeSubstance;

    if (!activeSubstanceLat.isEmpty()) {
        fullName += " (" + activeSubstanceLat + ")";
    }

    return fullName;
}

QString Drug::getBrands(QString separator) const {
    QString brands;

    for (const QString &brand : brandNames)
        brands += brand + separator;
    brands.resize(brands.size() - separator.size());

    return brands;
}
}
