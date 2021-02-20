#include "medicines.h"

namespace medicine {

Drug::Drug(const QString& activeSubstance,
           const QString& activeSubstanceLat,
           bool isPrescription,
           const std::vector<ReleaseForm>& releaseForms,
           const std::vector<QString>& brandNames,
           const std::vector<QString>& dosages,
           float price)
    : activeSubstance_(activeSubstance)
    , activeSubstancetLat_(activeSubstanceLat)
    , isPrescription_(isPrescription)
    , releaseForms_(releaseForms)
    , brandNames_(brandNames)
    , dosages_(dosages)
    , price_(price)
{
}

QString Drug::activeSubstance() const {
    return activeSubstance_;
}

QString Drug::activeSubstancetLat() const {
    return activeSubstancetLat_;
}

bool Drug::isPrescription() const {
    return isPrescription_;
}

std::vector<ReleaseForm> Drug::releaseForms() const {
    return releaseForms_;
}

std::vector<QString> Drug::brandNames() const {
    return brandNames_;
}

std::vector<Dosage> Drug::dosages() const {
    return dosages_;
}

float Drug::price() const {
    return price_;
}

QString Drug::getFullName() const {
    QString fullName = activeSubstance_;

    if (activeSubstancetLat_.size())
        fullName += " (" + activeSubstancetLat_ + ")";

    return fullName;
}

QString Drug::getBrands(QString separator) const {
    QString brands;

    for (QString brand : brandNames_)
        brands += brand + separator;
    brands.resize(brands.size() - separator.size());

    return brands;
}

bool Drug::operator ==(const Drug& other) {
    return activeSubstance_ == other.activeSubstance() &&
           activeSubstancetLat_ == other.activeSubstancetLat() &&
           isPrescription_ == other.isPrescription() &&
           releaseForms_ == other.releaseForms() &&
           brandNames_ == other.brandNames() &&
           dosages_ == other.dosages();
}

const std::vector<ReleaseForm>& releaseForms() {
    static std::vector<ReleaseForm> releaseForms = {
        "Ампулы (раствор для инъекций)",
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
        "Экстракт (настойка)"
    };
    return releaseForms;
}

}
