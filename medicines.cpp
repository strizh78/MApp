#include "medicines.h"

using namespace drugs;

Drug::Drug() {
    price_ = 0.0;
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

float Drug::price() const {
    return price_;
}

void Drug::setPrice(float price) {
    price_ = price;
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

QString Drug::getFullName() const {
    QString fullName = activeSubstance_;

    if (activeSubstancetLat_.size())
        fullName += " (" + activeSubstancetLat_ + ")";

    return fullName;
}




