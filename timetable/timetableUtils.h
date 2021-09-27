#pragma once

#include "event.h"
#include "appointment/appointment.h"

#include "database/databaseInterface.h"

bool isTimeSlotsIntersect(QDateTime b1, QDateTime e1, QDateTime b2, QDateTime e2);

int toSeconds(const QTime& time);

template <typename T>
bool isTimeSlotAvailable(DatabaseInterface* db, const T& obj, QDateTime dateTime, QTime duration) {
    QDateTime end = dateTime.addSecs(toSeconds(duration));

    std::vector <Appointment> a;
    db->appointment->list(a);
    for (const auto& x : a) {
        if (x != obj &&
            isTimeSlotsIntersect(dateTime, end, x.date, x.date.addSecs(toSeconds(x.service.duration))))
        {
            return false;
        }
    }

    std::vector <Event> e;
    db->event->list(e);
    for (const auto& x : e) {
        if (x != obj &&
            isTimeSlotsIntersect(dateTime, end, x.dateTime, x.dateTime.addSecs(toSeconds(x.duration)))) {
            return false;
        }
    }
    return true;
}
