#pragma once

#include "timetableEntry.h"

class TimetableEvent : public TimetableEntry {
public:
    TimetableEvent(const Event& event, const TimetableDrawSettings& settings);

    void openForm(std::shared_ptr<DatabaseInterface> database, QWidget* parent, bool show = true) const override;
    bool tryMoveEntry(const QTime& diff, std::shared_ptr<DatabaseInterface> database,
                      int minHour, int maxHour) override;

    bool isDateEquals(const QDate& timetableDate) const override;

private:
    Event event;
};
