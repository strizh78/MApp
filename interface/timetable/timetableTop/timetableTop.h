#pragma once

#include "database/databaseInterface.h"

#include <QLabel>
#include <QWidget>

class DailyTimeline;
class TimetableEvent;
class ComboBox;

class TimetableTop : public QWidget {
    Q_OBJECT
public:
    TimetableTop(QWidget* parent);

    void setDate(QDate date);
    void setDatabase(DatabasePtr database);
    void updateData(const std::vector<TimetableEvent>& tevents);

private slots:
    void processCreateEventBox();

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    QLabel* title_;
    ComboBox* createEventBox_;
    DailyTimeline* timeline_;

    DatabasePtr database_;

    int minimizedHeight_ = 152;
};

