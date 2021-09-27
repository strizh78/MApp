#include "serviceTestDB.h"

template <>
std::vector<Service> ItemDBTestInterface<Service>::list_ = {};
template <>
int ItemDBTestInterface<Service>::code_ = 0;

ServicesDBTest::ServicesDBTest() {
    const std::vector<Service> servicesList = {
        Service("Прием мануального терапевта (20 мин.)",  800, QTime(0, 20), false),
        Service("Прием мануального терапевта (30 мин.)", 1200, QTime(0, 30), false),
        Service("Прием мануального терапевта (60 мин.)", 2000, QTime(1, 00), false),

        Service("Растяжка позвоночника - дети (до 15 лет)",      300, QTime(0, 20), false),
        Service("Растяжка позвоночника - взрослые (от 15 лет)",  400, QTime(0, 30), false),
        Service("Растяжка позвоночника + массаж шеи - взрослые", 600, QTime(0, 30), false),

        Service("Mануальная терапия шейного отдела позвоночника", 1620.50, QTime(1, 0), true),
        Service("Мануальная терапия при заболеваниях суставов (плечевой, локтевой, лучезапястный)", 1495, QTime(1, 20), true),
        Service("Онлайн-консультация в зуме/телеграмме", 10000, QTime(0, 40), true),
        };
    for (auto service : servicesList)
        add(service);
}
