#pragma once

#include <QString>

#include <vector>

namespace medicine {

enum class ReleaseForms {
    PILLS,
    GRANULES,
    POWDER,
    CAPSULES,
    DRAGEE,
    OINTMENT,
    LINIMENT,
    PASTE,
    CANDLE,
    SOLUTION,
    BROTH,
    EXTRACT,
    MIXTURE
};

class Drug
{
public:
    Drug() = default;
    Drug(const QString& activeSubstance,
         const QString& activeSubstancetLat,
         bool isPrescription,
         const std::vector<ReleaseForms>& releaseForms,
         const std::vector<QString>& brandNames,
         const std::vector<QString>& dosages,
         float price);

    QString activeSubstance() const;
    void setaAtiveSubstance(const QString&);

    QString activeSubstancetLat() const;
    void setActiveSubstanceLat(const QString&);

    bool isPrescription() const;
    void setIsPrescription(bool);

    std::vector<ReleaseForms> releaseForms() const;
    void setReleaseForms(const std::vector<ReleaseForms>&);

    std::vector<QString> brandNames() const;
    void setBrandNames(const std::vector<QString>&);

    std::vector<QString> dosages() const;
    void setDosages(const std::vector<QString>&);

    float price() const;
    void setPrice(float);

    QString getFullName() const;

private:
    QString activeSubstance_;
    QString activeSubstancetLat_;
    bool isPrescription_;
    std::vector<ReleaseForms> releaseForms_;
    std::vector<QString> brandNames_;
    std::vector<QString> dosages_;
    float price_;

};

}
