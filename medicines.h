#pragma once

#include <QObject>
#include <QString>

#include <vector>

namespace drugs {

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
    Drug();
    QString activeSubstance() const;
    void setaAtiveSubstance(const QString&);
    QString activeSubstancetLat() const;
    void setActiveSubstanceLat(const QString&);
    float price() const;
    void setPrice(float);
    std::vector<ReleaseForms> releaseForms() const;
    void setReleaseForms(const std::vector<ReleaseForms>&);
    std::vector<QString> brandNames() const;
    void setBrandNames(const std::vector<QString>&);
    std::vector<QString> dosages() const;
    void setDosages(const std::vector<QString>&);

    QString getFullName() const;

private:
    QString activeSubstance_;
    QString activeSubstancetLat_;
    unsigned short price_;
    std::vector<ReleaseForms> releaseForms_;
    std::vector<QString> brandNames_;
    std::vector<QString> dosages_;

};

}
