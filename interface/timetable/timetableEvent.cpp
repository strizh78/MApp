#include "timetableEvent.h"

TimetableEvent::TimetableEvent(const Appointment &a)
    : begin(a.date.time())
    , end(a.date.time().addSecs(toSeconds(a.service.duration)))
    , name(a.patient.nameInfo.getFullName())
    , comment (a.service.name)
    , shortName(a.patient.nameInfo.getInitials())
    , date(a.date.date())
    , appointment(a)
    , type(APPOINTMENT)
{}

TimetableEvent::TimetableEvent(const Event &e)
    : begin(e.dateTime.time())
    , end(e.dateTime.time().addSecs(toSeconds(e.duration)))
    , name(e.title)
    , comment (e.comment)
    , shortName(e.title)
    , date(e.dateTime.date())
    , event(e)
    , type(EVENT)
{}

bool TimetableEvent::operator ==(const TimetableEvent &other) {
    return begin == other.begin;
}
