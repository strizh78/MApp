#pragma once

#include "interface/timetable/dailyTimetable.h"

#include <QWidget>

namespace Ui {
class EventForm;
}

class EventForm : public QWidget {
    Q_OBJECT

public:
    enum OpenMode {
        CREATE,
        EDIT
    };

public:
    explicit EventForm(std::shared_ptr<DatabaseInterface> database,
                       std::optional<Event> event = std::nullopt,
                       OpenMode mode = OpenMode::CREATE,
                       QWidget *parent = nullptr);
    ~EventForm();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

signals:
    void created(Event);
    void edited(Event);

private:
    Ui::EventForm *ui;
    std::shared_ptr<DatabaseInterface> database_;

    Event event_;
    OpenMode mode_;
};
