#include "drug.h"

Drug::Drug(QObject *parent) : QObject(parent) {
}

QString Drug::actSubst() const {
    return actSubst_;
}

void Drug::setActSubst(QString actSubst)
{
    actSubst_ = actSubst;
}

QString Drug::actSubstLat() const {
    return actSubstLat_;
}

void Drug::setActSubstLat(QString actSubstLat) {
    actSubstLat_ = actSubstLat;
}

unsigned short Drug::price() const {
    return price_;
}

void Drug::setPrice(unsigned short price) {
    price_ = price;
}

std::vector<ReleaseForms> Drug::releaseForms() const {
    return releaseForms_;
}

void Drug::setReleaseForms(std::vector<ReleaseForms> releaseForms) {
    releaseForms_ = releaseForms;
}

std::vector<QString> Drug::brandNames() const {
    return brandNames_;
}

void Drug::setBrandNames(std::vector<QString> brandNames) {
    brandNames_ = brandNames;
}

std::vector<QString> Drug::dosages() const {
    return dosages_;
}

void Drug::setDosages(std::vector<QString> dosages) {
    dosages_ = dosages;
}

QString Drug::view() const {
    QString drugView = actSubst_;

    if (actSubstLat_.size())
        drugView += " (" + actSubstLat_ + ")";

    return drugView;
}




