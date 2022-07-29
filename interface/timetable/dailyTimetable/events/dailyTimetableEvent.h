#pragma once

#include "interface/timetable/timetableEvent.h"

#include "database/databaseInterface.h"

#include <QAbstractButton>
#include <QLabel>
#include <QPushButton>

class DailyTimetableEvent : public QAbstractButton {
public:
    DailyTimetableEvent(const TimetableEvent& ev, DatabasePtr database, QWidget *parent);

    void setButtonsVisible(bool visible);

public slots:
    void update();
    void mouseDoubleClickEvent(QMouseEvent *e) override;

private slots:
    void openTimetableEventForm();

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    TimetableEvent event_;
    DatabasePtr database_;

    QLabel* name_, *time_, *comment_;
    QPushButton *buttonEdit_;
};
