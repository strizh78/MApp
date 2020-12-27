#pragma once

#include <QString>

#include <vector>

namespace homeopathy {

enum class Groups {
    MINERALS,
    PLANTS,
    ANIMALS,
    IMMATERIAL
};

enum class Dilutions {
    D6,
    D12,
    C3,
    C6,
    C12,
    C30,
    C200,
    C1000 = 1000,
    M1 = 1000,
    M10,
    M50,
    LM1,
    LM2,
    LM3,
    LM4,
    LM5,
    LM6,
    LM7,
    LM8,
    LM9,
    LM10,
    LM11,
    LM12
};

class Drug
{
public:
    Drug() = default;
    Drug(const QString& name,
         const QString& nameLat,
         Groups group,
         const std::vector<Dilutions>& dilutions,
         bool available);

    QString name() const;
    void setName(const QString& name);

    QString nameLat() const;
    void setNameLat(const QString& nameLat);

    Groups group() const;
    void setGroup(Groups group);

    std::vector<Dilutions> availableDilutions() const;
    void setAvailableDilutions(const std::vector<Dilutions>& availableDilutions);

    bool isAvailable() const;
    void setAvailable(bool available);

    QString getFullName() const;

private:
    QString name_;
    QString nameLat_;
    Groups group_;
    std::vector<Dilutions> availableDilutions_;
    bool isAvailable_;
};

}
