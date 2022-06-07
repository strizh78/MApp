#pragma once

#include "database/databaseInterface.h"

#include <QWidget>

class TimetableEvent;

class DailyTimetable : public QWidget {
public:
    DailyTimetable(QWidget *parent = 0);

    void setDate(QDate date);
    void setDatabase(DatabasePtr database);

    void updateData(const std::vector<TimetableEvent>& tevents);

private:
    QDate date_;
    DatabasePtr database_;
};
