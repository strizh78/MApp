#include "databasetest.h"

#include <QVariant>

#include <algorithm>

std::vector<Service> DatabaseTest::servicesList_ = DatabaseTest::initServices();
std::vector<medicine::Drug> DatabaseTest::medicinesList_ = DatabaseTest::initMedicineDrugs();

void DatabaseTest::homeopathyDrugs(std::vector<homeopathy::Drug>& receiver) {
    using namespace homeopathy;

    const std::vector<Dilutions> d1 = {
        Dilutions::C30,
        Dilutions::C200,
        Dilutions::C1000};
    const std::vector<Dilutions> d2 = {
        Dilutions::C30,
        Dilutions::C1000,
        Dilutions::LM1};
    const std::vector<Dilutions> d3 = {
        Dilutions::M1,
        Dilutions::LM6,
        Dilutions::C12};
    const std::vector<Dilutions> d4 = {
        Dilutions::M1,
        Dilutions::LM6,
        Dilutions::M10,
        Dilutions::LM10};
    receiver = {
        Drug("nameA", "nameLatA", Groups::ANIMALS, d1, true),
        Drug("nameB", "nameLatB", Groups::IMMATERIAL, d2, false),
        Drug("nameC", "nameLatC", Groups::MINERALS, d3, true),
        Drug("nameE", "nameLatE", Groups::ANIMALS, d4, false),
        Drug("nameF", "nameLatF", Groups::IMMATERIAL, d3, true),
        Drug("nameG", "nameLatG", Groups::MINERALS, d2, true),
        Drug("nameH", "nameLatH", Groups::PLANTS, d1, true),
        Drug("nameI", "nameLatI", Groups::ANIMALS, d1, false),
        Drug("nameJ", "nameLatJ", Groups::IMMATERIAL, d2, true),
        Drug("nameK", "nameLatK", Groups::MINERALS, d3, true)};
}

void DatabaseTest::availableHomeopathyDrugs(std::vector<homeopathy::Drug>& receiver) {
    using namespace homeopathy;

    const std::vector<Dilutions> d1 = {
        Dilutions::C30,
        Dilutions::C200,
        Dilutions::C1000};
    const std::vector<Dilutions> d2 = {
        Dilutions::C30,
        Dilutions::C1000,
        Dilutions::LM1};
    const std::vector<Dilutions> d3 = {
        Dilutions::M1,
        Dilutions::LM6,
        Dilutions::C12};
    const std::vector<Dilutions> d4 = {
        Dilutions::M1,
        Dilutions::LM6,
        Dilutions::M10,
        Dilutions::LM10};
    receiver = {
        Drug("nameA", "nameLatA", Groups::ANIMALS, d1, true),
        Drug("nameC", "nameLatC", Groups::MINERALS, d3, true),
        Drug("nameD", "nameLatD", Groups::PLANTS, d4, true),
        Drug("nameF", "nameLatF", Groups::IMMATERIAL, d3, true),
        Drug("nameG", "nameLatG", Groups::MINERALS, d2, true),
        Drug("nameH", "nameLatH", Groups::PLANTS, d1, true),
        Drug("nameJ", "nameLatJ", Groups::IMMATERIAL, d2, true),
        Drug("nameK", "nameLatK", Groups::MINERALS, d3, true)};

}

const std::vector<medicine::Drug> DatabaseTest::initMedicineDrugs() {
    using namespace medicine;

    auto allReleaseForms = releaseForms();
    const std::vector<ReleaseForm> relForms1 = {
        allReleaseForms[0],
        allReleaseForms[1],
        allReleaseForms[2]};
    const std::vector<ReleaseForm> relForms2 = {
        allReleaseForms[2],
        allReleaseForms[5],
        allReleaseForms[1]};
    const std::vector<ReleaseForm> relForms3 = {
        allReleaseForms[6],
        allReleaseForms[7],
        allReleaseForms[8]};
    const std::vector<ReleaseForm> relForms4 = {
        allReleaseForms[4],
        allReleaseForms[9],
        allReleaseForms[10]};
    const std::vector<QString> brands1 = {
        "brandA",
        "brandB",
        "brandC"};
    const std::vector<QString> brands2 = {
        "brandA"};
    const std::vector<QString> brands3 = {
        "brandB",
        "brandD"};
    const std::vector<QString> dosages1 = {
        "10-12, dos1",
        "12-16, dos2",
        "16+ dos3"};
    const std::vector<QString> dosages2 = {
        "1-12 мес., dos3",
        "1-10, dos4",
        "10-18+ dos5"};
    const std::vector<QString> dosages3 = {
        "2-3, dos6",
        "3-4, dos7",
        "4-16 dos8"};
    const std::vector<QString> dosages4 = {
        "dos9"};
    const std::vector<medicine::Drug> medicines = {
        Drug("actSubsA", "actSubsLatA", false, relForms1, brands1, dosages1, 3.14),
        Drug("actSubsB", "", false, relForms2, brands1, dosages1, 2.71),
        Drug("actSubsC", "actSubsLatC", false, relForms3, brands2, dosages2, 60.22),
        Drug("actSubsD", "actSubsLatD", true, relForms4, brands1, dosages1, 59.7),
        Drug("actSubsE", "actSubsLatE", false, relForms1, brands2, dosages2, 1989.1),
        Drug("actSubsF", "actSubsLatF", false, relForms2, brands3, dosages3, 9.1),
        Drug("actSubsG", "", false, relForms3, brands1, dosages1, 16.18),
        Drug("actSubsH", "actSubsLatH", false, relForms4, brands2, dosages2, 141.42),
        Drug("actSubsI", "actSubsLatI", true, relForms1, brands3, dosages3, 1202.05),
        Drug("actSubsJ", "actSubsLatJ", false, relForms1, brands3, dosages4, 1997.11),
        Drug("actSubsK", "", false, relForms2, brands2, dosages1, 379),
        Drug("actSubsL", "actSubsLatL", false, relForms3, brands1, dosages2, 1248),
        Drug("actSubsM", "actSubsLatM", false, relForms4, brands1, dosages3, 139),
        Drug("actSubsO", "", false, relForms4, brands2, dosages4, 525),
        Drug("actSubsP", "actSubsLatO", true, relForms1, brands3, dosages4, 636)};
    return medicines;
}

void DatabaseTest::medicineDrugs(std::vector<medicine::Drug>& receiver) {
    receiver = medicinesList_;
}

void DatabaseTest::addMedicineDrug(const medicine::Drug& drug) {
    medicinesList_.push_back(drug);
}

void DatabaseTest::editMedicineDrug(const medicine::Drug& oldDrug,
                                    const medicine::Drug& newDrug) {
    auto it = std::find(medicinesList_.begin(), medicinesList_.end(), oldDrug);
    *it = newDrug;
}

const std::vector<Service> DatabaseTest::initServices() {
    static const QTime duration1(/*hours*/ 1, /*mins*/ 30);
    static const QTime duration2(0, 45);
    static const QTime duration3(2, 0);

    static const std::vector<Service> servicesList = {
        Service("nameA", 1000, duration1, false),
        Service("nameB", 100.99, duration2, true),
        Service("nameC", 200.5, duration3, true),
        Service("long long long long nameD", 1.0, duration1, false),
        Service("really long long long long long long long nameE", 5000, duration2, false),
        Service("nameF", 2.5, duration3, true),
        Service("nameG", 10000, duration1, false)
    };

    return servicesList;
}

void DatabaseTest::services(std::vector<Service>& receiver) {
    receiver = servicesList_;
}

void DatabaseTest::notDeprecatedServices(std::vector<Service>& receiver) {
    Q_UNUSED(receiver);
}

void DatabaseTest::addService(const Service& newService) {
    servicesList_.push_back(newService);
}

void DatabaseTest::editService(const Service& oldService,
                               const Service& editedService)
{
    auto it = std::find(servicesList_.begin(), servicesList_.end(), oldService);
    *it = editedService;
}
