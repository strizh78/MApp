#include "homeopathy.h"

namespace homeopathy {

Drug::Drug(const QString& name,
           const QString& nameLat,
           Groups group,
           const std::vector<Dilutions>& dilutions,
           bool available)
    : name_(name)
    , nameLat_(nameLat)
    , group_(group)
    , availableDilutions_(dilutions)
    , isAvailable_(available)
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

std::vector<Dilutions> Drug::availableDilutions() const {
    return availableDilutions_;
}

bool Drug::isAvailable() const {
    return isAvailable_;
}

QString Drug::getFullName() const {
    QString fullName = name_;

    if (nameLat_.size())
        fullName += " (" + nameLat_ + ")";

    return fullName;
}

}
