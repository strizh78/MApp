#include "eventTestDB.h"

#include <QTime>

#include <vector>

template <>
std::vector<Event> ItemDBTestInterface<Event>::list_ = {};
template <>
int ItemDBTestInterface<Event>::code_ = 0;

EventDBTest::EventDBTest() {
    QDate today = QDate::currentDate();
    QDate yesterday = QDate::currentDate().addDays(-1);
    QDate tomorrow = QDate::currentDate().addDays(1);

    std::vector<Event> eventsList = {
        Event({"Обед", QDateTime(today, {16, 30}), QTime(0, 30)}),

        Event({"Зайти в МФЦ, которое находится на щукинской (не забыть документы)",
               QDateTime(tomorrow, {15, 10}), QTime(2, 0)}),
        Event({"Забрать дочь из обучащего заведения", QDateTime(tomorrow, {9, 45}), QTime(0, 20)}),
        Event({"Обед (в кафе?)", QDateTime(tomorrow, {19, 45}), QTime(0, 30)}),

        Event({"Сходить прогуляться", QDateTime(yesterday, {21, 0}), QTime(0, 35)}),
        Event({"забрать заказ wildberries", QDateTime(yesterday, {11, 50}), QTime(1, 10)})
    };

    eventsList[0].comment = "- Суп Том Ям\n- Фрикадельки в брусничном соусе\n- Яблочный сок\n";

    for (auto event : eventsList)
        add(event);
}
