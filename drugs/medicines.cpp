#include "medicines.h"

namespace medicine {

Drug::Drug(const QString& activeSubstance,
           const QString& activeSubstanceLat,
           bool isPrescription,
           const std::vector<ReleaseForms>& releaseForms,
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

void Drug::setaAtiveSubstance(const QString& activeSubstance)
{
    activeSubstance_ = activeSubstance;
}

QString Drug::activeSubstancetLat() const {
    return activeSubstancetLat_;
}

void Drug::setActiveSubstanceLat(const QString& activeSubstancetLat) {
    activeSubstancetLat_ = activeSubstancetLat;
}

bool Drug::isPrescription() const {
    return isPrescription_;
}

void Drug::setIsPrescription(bool isPrescription) {
    isPrescription_ = isPrescription;
}

std::vector<ReleaseForms> Drug::releaseForms() const {
    return releaseForms_;
}

void Drug::setReleaseForms(const std::vector<ReleaseForms>& releaseForms) {
    releaseForms_ = releaseForms;
}

std::vector<QString> Drug::brandNames() const {
    return brandNames_;
}

void Drug::setBrandNames(const std::vector<QString>& brandNames) {
    brandNames_ = brandNames;
}

std::vector<QString> Drug::dosages() const {
    return dosages_;
}

void Drug::setDosages(const std::vector<QString>& dosages) {
    dosages_ = dosages;
}

float Drug::price() const {
    return price_;
}

void Drug::setPrice(float price) {
    price_ = price;
}

QString Drug::getFullName() const {
    QString fullName = activeSubstance_;

    if (activeSubstancetLat_.size())
        fullName += " (" + activeSubstancetLat_ + ")";

    return fullName;
}

}



