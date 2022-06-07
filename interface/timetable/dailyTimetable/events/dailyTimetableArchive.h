#pragma once

#include <database/databaseInterface.h>

#include <QAbstractButton>
#include <QLabel>
#include <QPushButton>

class TimetableEvent;

class DailyTimetableArchive : public QAbstractButton {
public:
    DailyTimetableArchive(DatabasePtr database, QWidget *parent);

    void addEvent(const TimetableEvent& event);

public slots:
    void update();

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    QLabel* title_;
    QPushButton* buttonExpand_;
    DatabasePtr database_;
};
