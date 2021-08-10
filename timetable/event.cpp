#include "event.h"

Event::Event(QString title, QDateTime dateTime, QTime duration)
    : title(title)
    , dateTime(dateTime)
    , duration(duration)
{}

bool Event::operator < (const Event& other) const {
    return dateTime < other.dateTime;
}
