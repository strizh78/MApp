#include "homeopathyTestDB.h"

template <>
std::vector<homeopathy::Drug> ItemDBTestInterface<homeopathy::Drug>::list_ = {};
template <>
int ItemDBTestInterface<homeopathy::Drug>::code_ = 0;

HomeopathyDBTest::HomeopathyDBTest() {
    using namespace homeopathy;

    const std::vector<QString> d1 = {
        DILUTIONS[0],
        DILUTIONS[1],
        DILUTIONS[2]};
    const std::vector<QString> d2 = {
        DILUTIONS[3],
        DILUTIONS[4],
        DILUTIONS[5]};
    const std::vector<QString> d3 = {
        DILUTIONS[6],
        DILUTIONS[7],
        DILUTIONS[8]};
    const std::vector<QString> d4 = {
        DILUTIONS[0],
        DILUTIONS[3],
        DILUTIONS[4]};
    const std::vector<homeopathy::Drug> homeopathyDrugs = {
        Drug("Арсеникум альбум", "Arsenicum album", Groups::PLANTS, d1),
        Drug("Этиопс минералис", "Aethiops mineralis", Groups::MINERALS, d2),
        Drug("Ульмус фульва", "Ulmus fulva", Groups::PLANTS, d3),
        Drug("Прунус виргиниана", "Prunus virginiana", Groups::PLANTS, d4),
        Drug("Хелоне глабра", "Chelone glabra", Groups::PLANTS, d3),
        Drug("Ванадиум металликум", "Vanadium metallicum", Groups::MINERALS, d2),
        Drug("Стронтиум нитрикум", "Strontium nitricum", Groups::MINERALS, d1),
        Drug("Кониинум броматум", "Coniinum bromatum", Groups::MINERALS, d1),
        Drug("Гомерия коллина", "Homeria collina", Groups::PLANTS, d2),
        Drug("Симфитум оффицинале", "Symphytum officinale", Groups::PLANTS, d3)};

    for (auto drug : homeopathyDrugs)
        add(drug);
}
