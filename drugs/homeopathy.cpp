#include "homeopathy.h"

namespace homeopathy {

Drug::Drug(const QString& name,
           const QString& nameLat,
           const Groups group,
           const std::vector<QString>& dilutions)
    : name(name)
    , nameLat(nameLat)
    , group(group)
    , availableDilutions(dilutions)
{
}

bool Drug::isAvailable() const {
    return !availableDilutions.empty();
}

QString Drug::getFullName() const {
    if (name.isEmpty())
        return  nameLat;

    QString fullName = name;

    if (!nameLat.isEmpty())
        fullName += " (" + nameLat + ")";

    return fullName;
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
