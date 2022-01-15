#include "timetableForm.h"
#include "ui_timetableForm.h"

#include "event/eventForm.h"

#include "interface/interfaceUtils.h"

TimetableForm::TimetableForm(std::shared_ptr<DatabaseInterface> database, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimetableForm)
    , database_(database)
{
    ui->setupUi(this);

    ui->dailyTimetable->setDatabase(database_);
}

TimetableForm::~TimetableForm() {
    delete ui;
}

void TimetableForm::on_addEventBtn_clicked() {
    QDateTime eventDateTime(ui->calendarWidget->selectedDate(),
                            QTime(QTime::currentTime().hour(), 0));
    Event event(/*event name*/ "", eventDateTime, /*duration*/ QTime(1, 0));

    auto* form = new EventForm(database_, event, EventForm::OpenMode::CREATE, this);
    connect(form, SIGNAL(created(Event)), ui->dailyTimetable, SLOT(update()));

    showAsWindowModal(form);
}

void TimetableForm::on_leftDateBtn_clicked() {
    setDate(ui->calendarWidget->selectedDate().addDays(-1));
}

void TimetableForm::on_rightDateBtn_clicked() {
    setDate(ui->calendarWidget->selectedDate().addDays(1));
}

void TimetableForm::on_todayDateBtn_clicked() {
    setDate(QDate::currentDate());
}

void TimetableForm::on_calendarWidget_activated(const QDate &date) {
    ui->dailyTimetable->setDate(date);
}

void TimetableForm::on_calendarWidget_clicked(const QDate &date) {
    ui->dailyTimetable->setDate(date);
}

void TimetableForm::setDate(const QDate& date) {
    ui->dailyTimetable->setDate(date);
    ui->calendarWidget->setSelectedDate(date);
}
