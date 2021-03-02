#include "homeopathy.h"

namespace homeopathy {

Drug::Drug(const QString& name,
           const QString& nameLat,
           const Groups group,
           const std::vector<QString>& dilutions)
    : name_(name)
    , nameLat_(nameLat)
    , group_(group)
    , availableDilutions_(dilutions)
{
}

QString Drug::name() const {
    return name_;
}

QString Drug::nameLat() const {
    return nameLat_;
}

Groups Drug::group() const {
    return group_;
}

std::vector<QString> Drug::availableDilutions() const {
    return availableDilutions_;
}

bool Drug::isAvailable() const {
    return !availableDilutions_.empty();
}

QString Drug::getFullName() const {
    if (name_.isEmpty())
        return  nameLat_;

    QString fullName = name_;

    if (!nameLat_.isEmpty())
        fullName += " (" + nameLat_ + ")";

    return fullName;
}

bool Drug::operator ==(const Drug& other) {
    return name_ == other.name() &&
           nameLat_ == other.nameLat() &&
           group_ == other.group() &&
           availableDilutions_ == other.availableDilutions_;
}

QString groupToString(Groups group) {
   switch (group) {
       case Groups::ANIMALS:
           return "Животные";
       case Groups::MINERALS:
           return "Минералы";
       case Groups::IMMATERIAL:
           return "Неживое";
       case Groups::PLANTS:
           return "Растения";
       default:
           return "";
   }
}

}
