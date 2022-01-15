#include "eventForm.h"
#include "ui_eventForm.h"

#include "interface/interfaceUtils.h"
#include "timetable/timetableUtils.h"

namespace {
    std::vector<QString> getInvalidFields(const Event& event, bool isNewEvent, DatabaseInterface* db) {
        std::vector<QString> wrongFields;
        if (event.title.isEmpty()) {
            wrongFields.push_back("Наименование");
        }

        if (event.duration == QTime(0, 0)) {
            wrongFields.push_back("Длительность");
        }

        QDateTime past10Mins = QDateTime::currentDateTime().addSecs(-10 * 60);
        if (isNewEvent && event.dateTime < past10Mins) {
            wrongFields.push_back("Время события уже прошло");
        }

        if (!isTimeSlotAvailable(db, event, event.dateTime, event.duration)) {
            wrongFields.push_back("Время для события уже занято");
        }

        return wrongFields;
    }
}

EventForm::EventForm(DatabasePtr database,
                     std::optional<Event> event,
                     OpenMode mode,
                     QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EventForm)
    , database_(database)
    , event_(event.value_or(Event("", QDateTime(QDate::currentDate(), QTime::currentTime()), QTime(1, 0))))
    , mode_(mode)
{
    ui->setupUi(this);
    ui->errorLabel->setVisible(false);

    ui->nameEdit->setText(event_.title);
    ui->beginDateEdit->setDateTime(event_.dateTime);
    ui->durationEdit->setTime(event_.duration);
    ui->commentEdit->setText(event_.comment);
}

EventForm::~EventForm() {
    delete ui;
}

void EventForm::on_buttonBox_accepted() {
    event_.title = ui->nameEdit->text();
    event_.dateTime = ui->beginDateEdit->dateTime();
    event_.duration = ui->durationEdit->time();
    event_.comment = ui->commentEdit->toPlainText();

    auto wrongFields = getInvalidFields(event_, (mode_ == OpenMode::CREATE), database_.get());
    if (!wrongFields.empty()) {
        ErrorLog::showItemFormWarning(ui->errorLabel, wrongFields);
        return;
    }

    if (mode_ == EDIT) {
        database_->event->update(event_);
        emit edited(event_);
    } else {
        database_->event->add(event_);
        emit created(event_);
    }

    close();
}

void EventForm::on_buttonBox_rejected() {
    close();
}
