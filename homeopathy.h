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
    bool isAvailable() const;
    void setAvailable(bool);
    QString name() const;
    void setName(const QString&);
    QString nameLat() const;
    void setNameLat(const QString&);
    Groups group() const;
    void setGroup(Groups);
    std::vector<Dilutions> availableDilutions() const;
    void setAvailableDilutions(const std::vector<Dilutions>&);

    QString getFullName() const;

private:
    bool isAvailable_;
    QString name_;
    QString nameLat_;
    Groups group_;
    std::vector<Dilutions> availableDilutions_;

};

}
