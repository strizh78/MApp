#pragma once

#include "database/databaseInterface.h"

#include "timetable/event.h"

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
    explicit EventForm(DatabasePtr database,
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
    DatabasePtr database_;

    Event event_;
    OpenMode mode_;
};
