#pragma once

#include "appointment/appointment.h"
#include "timetable/event.h"

#include "timetable/timetableUtils.h"

#include <QColor>

class TimetableEvent {
public:
    enum EventType {
        APPOINTMENT,
        EVENT
    };

    TimetableEvent(const Appointment& a);
    TimetableEvent(const Event& e);

    bool operator == (const TimetableEvent& other);

public:
    QTime begin;
    QTime end;
    QString name;
    QString comment = "";
    QString shortName = "";
    QColor color;
    QDate date;

    Appointment appointment;
    Event event;

    EventType type;
};
