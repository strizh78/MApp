#pragma once

#include "database/databaseinterface.h"

#include <QPainter>

class Event;
class Appointment;

struct TimetableDrawSettings {
    int firstTimetableHour = 8;
    int timetableHoursCount = 15;

    int width;
    int oneHourHeight = 60;
    int extraRectWidth = 5;
    int roundEntryRectRadius = 7;

    // start coordinates for the first timetable entry rectangle
    int startXCoordinate = 40;
    int startYCoordinate = 70;
};

class TimetableEntryDrawer {
public:
    TimetableEntryDrawer(const Appointment &appointment, const TimetableDrawSettings& settings);
    TimetableEntryDrawer(const Event &event, const TimetableDrawSettings& settings);

    void draw(QPainter &painter) const;
    void drawBackground(QPainter &painter) const;
    void drawText(QPainter &painter) const;

    QRect rect() const {
        return backgroundRect;
    }
private:
    void setColors(QColor baseColor, QColor extColor);
    void setFonts(QFont mainFont, QFont extraFont);
    void setRects();

private:
    // entry data
    QTime begin;
    QTime duration;

    QString entryTitle;
    QString entryExtraComment;

    // ui settings
    TimetableDrawSettings settings_;

    QRect backgroundRect;
    QColor backgroundColor;

    QRect extraBackRect;
    QColor extraColor;

    QRect textRect;
    QColor textColor;
    QFont titleFont;
    QFont extraTextFont;
};

class TimetableEntry {
public:
    template <typename T>
    TimetableEntry(const T &t, const TimetableDrawSettings& settings)
        : drawer(t, settings)
    {}

    void draw(QPainter& painter) const;
    bool rectContainsPoint(const QPoint &point) const;

    virtual void openForm(std::shared_ptr<DatabaseInterface> database, QWidget* parent, bool show = true) const = 0;
    virtual bool tryMoveEntry(const QTime& time, std::shared_ptr<DatabaseInterface> database,
                              int minHour, int maxHour) = 0;

    virtual bool isDateEquals(const QDate& timetableDate) const = 0;

protected:
    TimetableEntryDrawer drawer;
};

std::shared_ptr<TimetableEntry> getEntry(const Appointment& x, const TimetableDrawSettings& settings);
std::shared_ptr<TimetableEntry> getEntry(const Event& x, const TimetableDrawSettings& settings);
