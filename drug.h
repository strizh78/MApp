#ifndef DRUG_H
#define DRUG_H

#include <QObject>
#include <QString>
#include <vector>

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
    Q_PROPERTY(QString actSubst READ actSubst WRITE setActSubst);
    Q_PROPERTY(QString actSubstLat READ actSubstLat WRITE setActSubstLat);
    Q_PROPERTY(unsigned short price READ price WRITE setPrice);
    Q_PROPERTY(std::vector<ReleaseForms> releaseForms READ releaseForms WRITE setReleaseForms);
    Q_PROPERTY(std::vector<QString> brandNames READ brandNames WRITE setBrandNames);
    Q_PROPERTY(std::vector<QString> dosages READ dosages WRITE setDosages);

public:
    explicit Drug(QObject *parent = nullptr);
    QString actSubst() const;
    void setActSubst(QString);
    QString actSubstLat() const;
    void setActSubstLat(QString);
    unsigned short price() const;
    void setPrice(unsigned short);
    std::vector<ReleaseForms> releaseForms() const;
    void setReleaseForms(std::vector<ReleaseForms>);
    std::vector<QString> brandNames() const;
    void setBrandNames(std::vector<QString>);
    std::vector<QString> dosages() const;
    void setDosages(std::vector<QString>);

    QString view() const;

private:
    QString actSubst_;
    QString actSubstLat_;
    unsigned short price_;
    std::vector<ReleaseForms> releaseForms_;
    std::vector<QString> brandNames_;
    std::vector<QString> dosages_;

};

#endif // DRUG_H
