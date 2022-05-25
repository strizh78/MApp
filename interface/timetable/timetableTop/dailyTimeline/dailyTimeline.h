#pragma once

#include "database/databaseInterface.h"

#include <QWidget>

class TimetableEvent;
class DailyTimelineLine;
class DailyTimelineForm;

class DailyTimeline : public QWidget {
public:
    DailyTimeline(QWidget* parent);

    void updateData(const std::vector<TimetableEvent>& tevents);

    void setDate(QDate date);

    void setDatabase(DatabasePtr database);

private:
    DailyTimelineLine* line_;
    DailyTimelineForm* selectedEventForm_;
};
