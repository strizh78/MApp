#pragma once

#include "interface/basicForms/comboBox.h"

#include "interface/timetable/timetableEvent.h"

#include <QPushButton>
#include <QWidget>

class Appointment;

class DailyTimelineForm : public QWidget {
public:
    DailyTimelineForm(QWidget* parent);

public slots:
    void setTimetableEvent(TimetableEvent event);

public:
    QPushButton* acceptedButton;
    QPushButton* declinedButton;

private:
    ComboBox* name_;
    ComboBox* service_;
    ComboBox* time_;
};
