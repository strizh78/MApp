#include "eventEntry.h"

#include "interface/timetable/event/eventForm.h"

#include "interface/utils.h"
#include "timetable/timetableUtils.h"

std::shared_ptr<TimetableEntry> getEntry(const Event& x, const TimetableDrawSettings& settings) {
    return std::make_shared<TimetableEvent>(x, settings);
}

TimetableEvent::TimetableEvent(const Event &event, const TimetableDrawSettings &settings)
    : TimetableEntry(event, settings)
    , event(event)
{
}

void TimetableEvent::openForm(std::shared_ptr<DatabaseInterface> database, QWidget *parent, bool show) const {
    auto * eventViewForm = new EventForm(database, event, EventForm::EDIT, parent);
    parent->connect(eventViewForm, SIGNAL(edited(Event)),
                    parent, SLOT(update()));
    if (show) showAsWindowModal(eventViewForm);
    return;
}

bool TimetableEvent::isDateEquals(const QDate &timetableDate) const {
    return timetableDate == event.dateTime.date();
}

bool TimetableEvent::tryMoveEntry(const QTime &diff, std::shared_ptr<DatabaseInterface> database,
                                  int minHour, int maxHour)
{
    Event eventNew = event;
    eventNew.dateTime.setTime(event.dateTime.time().addSecs(diff.hour() * 60 * 60 + diff.minute() * 60));

    if (eventNew.dateTime.time() < QTime(minHour, 0) ||
        eventNew.dateTime.time() > QTime(maxHour, 0))
    {
        return false;
    }

    if (isTimeSlotAvailable(database.get(), eventNew, eventNew.dateTime, eventNew.duration)) {
        database->event->edit(eventNew, eventNew);
        return true;
    }
    return false;
}


