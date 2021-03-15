#pragma once

#include "MAppBaseObj/mappBaseObj.h"

#include <QString>
#include <QMetaType>

#include <vector>

using Dosage = QString;
using ReleaseForm = QString;

namespace medicine {

const std::vector<ReleaseForm> RELEASE_FORMS = {"Ампулы (раствор для инъекций)",
                                                "Бальзам (линимент)",
                                                "Гранулы",
                                                "Драже",
                                                "Капсулы",
                                                "Мазь",
                                                "Микстура",
                                                "Отвар (настой)",
                                                "Паста",
                                                "Порошок",
                                                "Раствор (для внутреннего или наружного применения)",
                                                "Свечи",
                                                "Таблетки",
                                                "Экстракт (настойка)"};

class Drug : public MAppBaseObj {
public:
    Drug() = default;
    Drug(const QString& activeSubstance,
         const QString& activeSubstancetLat,
         bool isPrescription,
         const std::vector<ReleaseForm>& releaseForms,
         const std::vector<QString>& brandNames,
         const std::vector<Dosage>& dosages,
         float price);

    QString activeSubstance() const;
    QString activeSubstancetLat() const;
    bool isPrescription() const;
    std::vector<ReleaseForm> releaseForms() const;
    std::vector<QString> brandNames() const;
    std::vector<Dosage> dosages() const;
    float price() const;

    QString getFullName() const;
    QString getBrands(QString separator = " ") const;

private:
    QString activeSubstance_;
    QString activeSubstancetLat_;
    bool isPrescription_;
    std::vector<ReleaseForm> releaseForms_;
    std::vector<QString> brandNames_;
    std::vector<Dosage> dosages_;
    float price_;
};

}

Q_DECLARE_METATYPE( medicine::Drug ); // for QVariant
Q_DECLARE_METATYPE( medicine::Drug*);
