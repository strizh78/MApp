#include "databasetest.h"
#include "homeopathy.h"
#include "medicines.h"

std::vector<homeopathy::Drug> DatabaseTest::homeopathyDrugs() {
    using namespace homeopathy;

    const std::vector<Dilutions> d1 = {Dilutions::C30,
                                      Dilutions::C200,
                                      Dilutions::C1000};
    const std::vector<Dilutions> d2 = {Dilutions::C30,
                                      Dilutions::C1000,
                                      Dilutions::LM1};
    const std::vector<Dilutions> d3 = {Dilutions::M1,
                                      Dilutions::LM6,
                                      Dilutions::C12};
    const std::vector<Dilutions> d4 = {Dilutions::M1,
                                      Dilutions::LM6,
                                      Dilutions::M10,
                                      Dilutions::LM10};

    std::vector<homeopathy::Drug> drugs;
    drugs.push_back(Drug("nameA", "nameLatA", Groups::ANIMALS, d1, true));
    drugs.push_back(Drug("nameB", "nameLatB", Groups::IMMATERIAL, d2, false));
    drugs.push_back(Drug("nameC", "nameLatC", Groups::MINERALS, d3, true));
    drugs.push_back(Drug("nameD", "nameLatD", Groups::PLANTS, d4, true));
    drugs.push_back(Drug("nameE", "nameLatE", Groups::ANIMALS, d4, false));
    drugs.push_back(Drug("nameF", "nameLatF", Groups::IMMATERIAL, d3, true));
    drugs.push_back(Drug("nameG", "nameLatG", Groups::MINERALS, d2, true));
    drugs.push_back(Drug("nameH", "nameLatH", Groups::PLANTS, d1, true));
    drugs.push_back(Drug("nameI", "nameLatI", Groups::ANIMALS, d1, false));
    drugs.push_back(Drug("nameJ", "nameLatJ", Groups::IMMATERIAL, d2, true));
    drugs.push_back(Drug("nameK", "nameLatK", Groups::MINERALS, d3, true));

    return drugs;
}

std::vector<homeopathy::Drug> DatabaseTest::availableHomeopathyDrugs() {

    using namespace homeopathy;

    const std::vector<Dilutions> d1 = {Dilutions::C30,
                                      Dilutions::C200,
                                      Dilutions::C1000};
    const std::vector<Dilutions> d2 = {Dilutions::C30,
                                      Dilutions::C1000,
                                      Dilutions::LM1};
    const std::vector<Dilutions> d3 = {Dilutions::M1,
                                      Dilutions::LM6,
                                      Dilutions::C12};
    const std::vector<Dilutions> d4 = {Dilutions::M1,
                                      Dilutions::LM6,
                                      Dilutions::M10,
                                      Dilutions::LM10};

    std::vector<homeopathy::Drug> drugs;
    drugs.push_back(Drug("nameA", "nameLatA", Groups::ANIMALS, d1, true));
    drugs.push_back(Drug("nameC", "nameLatC", Groups::MINERALS, d3, true));
    drugs.push_back(Drug("nameD", "nameLatD", Groups::PLANTS, d4, true));
    drugs.push_back(Drug("nameF", "nameLatF", Groups::IMMATERIAL, d3, true));
    drugs.push_back(Drug("nameG", "nameLatG", Groups::MINERALS, d2, true));
    drugs.push_back(Drug("nameH", "nameLatH", Groups::PLANTS, d1, true));
    drugs.push_back(Drug("nameJ", "nameLatJ", Groups::IMMATERIAL, d2, true));
    drugs.push_back(Drug("nameK", "nameLatK", Groups::MINERALS, d3, true));

    return drugs;
}

std::vector<medicine::Drug> DatabaseTest::medicineDrugs() {
    using namespace medicine;

    const std::vector<ReleaseForms> relForms1 = {ReleaseForms::BROTH,
                                                ReleaseForms::PILLS,
                                                ReleaseForms::DRAGEE};
    const std::vector<ReleaseForms> relForms2 = {ReleaseForms::DRAGEE,
                                                ReleaseForms::CAPSULES,
                                                ReleaseForms::OINTMENT};
    const std::vector<ReleaseForms> relForms3 = {ReleaseForms::EXTRACT,
                                                ReleaseForms::MIXTURE,
                                                ReleaseForms::DRAGEE};
    const std::vector<ReleaseForms> relForms4 = {ReleaseForms::POWDER,
                                                ReleaseForms::PILLS,
                                                ReleaseForms::MIXTURE};
    const std::vector<QString> brands1 = {"brandA",
                                         "brandB",
                                         "brandC"};
    const std::vector<QString> brands2 = {"brandA"};
    const std::vector<QString> brands3 = {"brandB",
                                         "brandD"};
    const std::vector<QString> dosages1 = {"10-12, dos1",
                                          "12-16, dos2",
                                          "16+ dos3"};
    const std::vector<QString> dosages2 = {"1-12 мес., dos3",
                                          "1-10, dos4",
                                          "10-18+ dos5"};
    const std::vector<QString> dosages3 = {"2-3, dos6",
                                          "3-4, dos7",
                                          "4-16 dos8"};
    const std::vector<QString> dosages4 = {"dos9"};

    std::vector<medicine::Drug> drugs;
    drugs.push_back(Drug("actSubsA", "actSubsLatA", false, relForms1, brands1, dosages1, 3.14));
    drugs.push_back(Drug("actSubsB", "", false, relForms2, brands1, dosages1, 2.71));
    drugs.push_back(Drug("actSubsC", "actSubsLatC", false, relForms3, brands2, dosages2, 60.22));
    drugs.push_back(Drug("actSubsD", "actSubsLatD", true, relForms4, brands1, dosages1, 59.7));
    drugs.push_back(Drug("actSubsE", "actSubsLatE", false, relForms1, brands2, dosages2, 1989.1));
    drugs.push_back(Drug("actSubsF", "actSubsLatF", false, relForms2, brands3, dosages3, 9.1));
    drugs.push_back(Drug("actSubsG", "", false, relForms3, brands1, dosages1, 16.18));
    drugs.push_back(Drug("actSubsH", "actSubsLatH", false, relForms4, brands2, dosages2, 141.42));
    drugs.push_back(Drug("actSubsI", "actSubsLatI", true, relForms1, brands3, dosages3, 1202.05));
    drugs.push_back(Drug("actSubsJ", "actSubsLatJ", false, relForms1, brands3, dosages4, 1997.11));
    drugs.push_back(Drug("actSubsK", "", false, relForms2, brands2, dosages1, 379));
    drugs.push_back(Drug("actSubsL", "actSubsLatL", false, relForms3, brands1, dosages2, 1248));
    drugs.push_back(Drug("actSubsM", "actSubsLatM", false, relForms4, brands1, dosages3, 139));
    drugs.push_back(Drug("actSubsO", "", false, relForms4, brands2, dosages4, 525));
    drugs.push_back(Drug("actSubsP", "actSubsLatO", true, relForms1, brands3, dosages4, 636));

    return drugs;
}
