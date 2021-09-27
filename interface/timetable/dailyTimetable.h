#pragma once

#include "interface/timetable/entries/timetableEntry.h"
#include "database/databaseInterface.h"

#include <QTimer>
#include <QWidget>

#include <set>

class DailyTimetable : public QWidget {
public:
    DailyTimetable(QWidget *parent = 0);

    void setDate(QDate date);
    void setDatabase(std::shared_ptr<DatabaseInterface> database);

    void updateData();

private slots:
    void update();

protected:
    void paintEvent(QPaintEvent *e) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void updatePainting();

    template <class EntryBase>
    void addEntries(std::vector<EntryBase> data);

    QRect addTimeRect(QPainter & painter, QTime beg, QTime end, QString name, QString text, QColor color);
    void drawTimeLine(QPainter & painter, QTime time, QColor color, bool needCircleMarker = false);

private:
    QDate date_;
    TimetableDrawSettings drawSettings_;
    std::set <std::shared_ptr<TimetableEntry>> timetableEntries_;

    std::shared_ptr<DatabaseInterface> database_;

    std::shared_ptr<TimetableEntry> movingEntry_ = nullptr;
    QPoint lastMovePosition_;
};
