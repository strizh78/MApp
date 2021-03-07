#pragma once

#include "MAppBaseObj/mappBaseObj.h"

#include <QString>
#include <QMetaType>

#include <vector>

namespace homeopathy {

enum class Groups {
    ANIMALS,
    MINERALS,
    IMMATERIAL,
    PLANTS,
    NUMBER_OF_GROUPS
};

const std::vector<QString> DILUTIONS = {
    "D6",
    "D12",
    "C3",
    "C6",
    "C12",
    "C30",
    "C200",
    "C1000 (M1)",
    "M10",
    "M50",
    "LM1",
    "LM2",
    "LM3",
    "LM4",
    "LM5",
    "LM6",
    "LM7",
    "LM8",
    "LM9",
    "LM10",
    "LM11",
    "LM12"
};

class Drug : public MAppBaseObj{
public:
    Drug() = default;
    Drug(const QString& name,
         const QString& nameLat,
         const Groups group,
         const std::vector<QString>& dilutions);

    QString name() const;
    QString nameLat() const;
    Groups group() const;
    std::vector<QString> availableDilutions() const;
    bool isAvailable() const;
    QString getFullName() const;

private:
    QString name_;
    QString nameLat_;
    Groups group_;
    std::vector<QString> availableDilutions_;
};

QString groupToString(Groups group);

}

Q_DECLARE_METATYPE(homeopathy::Drug); // for QVariant
Q_DECLARE_METATYPE(homeopathy::Groups);
