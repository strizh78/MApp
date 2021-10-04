#pragma once

#include "MAppBaseObj/mappBaseObj.h"
#include "dosage.h"

#include <QString>
#include <QMetaType>

#include <vector>

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
    Drug(const QString& name,
         const QString& activeSubstance,
         const QString& activeSubstancetLat,
         bool isPrescription,
         const std::vector<ReleaseForm>& releaseForms,
         const std::vector<QString>& brandNames,
         const std::vector<Dosage>& dosages,
         const QString& contraindications,
         float price);

    QString getFullName() const;
    QString getActiveSubstance() const;
    QString getBrands(QString separator = " ") const;

public:
    QString name;
    QString activeSubstance;
    QString activeSubstancetLat;
    bool isPrescription;
    std::vector<ReleaseForm> releaseForms;
    std::vector<QString> brandNames;
    std::vector<Dosage> dosages;
    QString contraindications;
    float price;
};

}

Q_DECLARE_METATYPE( medicine::Drug ); // for QVariant
Q_DECLARE_METATYPE( medicine::Drug*);
