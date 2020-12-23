#include "homeopathy.h"

namespace homeopathy {

bool Drug::isAvailable() const {
    return isAvailable_;
}

void Drug::setAvailable(bool available) {
    isAvailable_ = available;
}

QString Drug::name() const {
    return name_;
}

void Drug::setName(const QString& name) {
    name_ = name;
}

QString Drug::nameLat() const {
    return nameLat_;
}

void Drug::setNameLat(const QString& nameLat) {
    nameLat_ = nameLat;
}

Groups Drug::group() const {
    return group_;
}

void Drug::setGroup(Groups group) {
    group_ = group;
}

std::vector<Dilutions> Drug::availableDilutions() const {
    return availableDilutions_;
}

void Drug::setAvailableDilutions(const std::vector<Dilutions>& availableDilutions) {
    availableDilutions_ = availableDilutions;
}

QString Drug::getFullName() const {
    QString fullName = name_;

    if (nameLat_.size())
        fullName += " (" + nameLat_ + ")";

    return fullName;
}

}
