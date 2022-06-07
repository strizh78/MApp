#pragma once

#include "database/databaseInterface.h"

#include "interface/timetable/timetableEvent.h"

#include "timetable/timetableUtils.h"

#include <QObject>
#include <QWidget>

class DailyTimelineLine : public QWidget {
    Q_OBJECT
public:
    explicit DailyTimelineLine(QWidget* parent = nullptr);
    ~DailyTimelineLine() = default;

    void setDate(QDate date);
    void setDatabase(DatabasePtr database);

    void updateData(const std::vector<TimetableEvent>& tevents_);

signals:
    void elementSelected(TimetableEvent event);

public slots:
    void unselect();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *e) override;
    void leaveEvent(QEvent *event) override;

private:
    void updateUIParams();
    TimetableEvent* tryFindEventByPoint(QPoint pos);

    void drawBasicTimeline(QPainter& painter);

    void drawTicks(QTime start, QTime end, QPainter& painter);
    void drawTick(QTime time, QPainter& painter, int tickHeightRedefine = 0);

    void drawInfoPopUp(QPainter& painter);

    void drawCurrentTime(QPainter& painter);

    int getXCoordByTime(QTime time);

private:
    QDate date_;
    std::vector<TimetableEvent> events_;
    DatabasePtr database_;

    TimetableEvent* selected_ = nullptr;
    TimetableEvent* hovered_ = nullptr;

// timetable params
    int firstHour_ = 8;
    int lastHour_ = 20;
    int numberOfHours_ = lastHour_ - firstHour_;

// UI params
    double timelineY_;
    double oneMinuteSize_;
    double xShift_;
};

