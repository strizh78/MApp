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

class Drug : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString activeSubstance READ activeSubstance WRITE setaAtiveSubstance );
    Q_PROPERTY(QString activeSubstanceLat READ activeSubstancetLat WRITE setActiveSubstanceLat);
    Q_PROPERTY(unsigned short price READ price WRITE setPrice);
    Q_PROPERTY(std::vector<ReleaseForms> releaseForms READ releaseForms WRITE setReleaseForms);
    Q_PROPERTY(std::vector<QString> brandNames READ brandNames WRITE setBrandNames);
    Q_PROPERTY(std::vector<QString> dosages READ dosages WRITE setDosages);

public:
    explicit Drug(QObject *parent = nullptr);
    QString activeSubstance() const;
    void setaAtiveSubstance(const QString&);
    QString activeSubstancetLat() const;
    void setActiveSubstanceLat(const QString&);
    unsigned short price() const;
    void setPrice(unsigned short);
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
