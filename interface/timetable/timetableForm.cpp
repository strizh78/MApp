#include "timetableForm.h"
#include "ui_timetableForm.h"

#include "timetableEvent.h"

#include "event/eventForm.h"

#include "interface/interfaceUtils.h"

TimetableForm::TimetableForm(std::shared_ptr<DatabaseInterface> database, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimetableForm)
    , database_(database)
{
    ui->setupUi(this);
    ui->monthComboBox->SetAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->monthComboBox->setContentsMargins(0, 0, 20, 0);
    ui->yearComboBox->SetAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->yearComboBox->setContentsMargins(35, 0, 0, 0);

    changeFont(ui->todayDateBtn, 18, QFont::Medium);
    changeFont(ui->yearComboBox, 18, QFont::Normal);
    changeFont(ui->monthComboBox, 18, QFont::Normal);

    // TODO spkhaykova: поддержать обновление через сигналы, учесть в интерфейсе сохранение визуала при обновлении
    startTimer(60 * 1e3, Qt::TimerType::VeryCoarseTimer);

    ui->dailyTimetable->setDatabase(database_);
    ui->timetableTop->setDatabase(database_);

    setDate(QDate::currentDate());

    connect(ui->calendarWidget, &CalendarWidget::dateChanged, this, &TimetableForm::calendarDateChanged);
}

void TimetableForm::timerEvent(QTimerEvent *event) {
    updateData();
}

void TimetableForm::updateData() {
    std::vector<TimetableEvent> tevents;

    std::vector<Appointment> appointments;
    database_->appointment->list(appointments);
    for (auto& v : appointments) {
        if (!v.isDeleted() && v.date.date() == date_) {
            tevents.push_back(v);
        }
    }

    std::vector<Event> events;
    database_->event->list(events);
    for (auto& v : events) {
        if (!v.isDeleted() && v.dateTime.date() == date_) {
            tevents.push_back(v);
        }
    }

    sort (tevents.begin(), tevents.end(), [](const TimetableEvent& a, const TimetableEvent& b) { return a.begin < b.begin; });

    std::vector <QColor> colors = {
                                    QColor(89, 142, 221),
                                    QColor(203, 92, 92),
                                    QColor(235, 174, 56),
                                    QColor(79, 161, 112)
                                  };
    for (size_t i = 0; i < tevents.size(); ++i) {
        tevents[i].color = colors[i % 4];
    }

    ui->dailyTimetable->updateData(tevents);
    ui->timetableTop->updateData(tevents);
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

void TimetableForm::calendarDateChanged(QDate date) {
    setDate(date);
}

void TimetableForm::setDate(const QDate& date) {
    date_ = date;
    ui->dailyTimetable->setDate(date);
    ui->timetableTop->setDate(date);
    ui->calendarWidget->setSelectedDate(date);

    ui->monthComboBox->setCurrentIndex(date.month() - 1);
    ui->yearComboBox->setCurrentText(date.toString("yyyy").toLower());

    updateData();
}

void TimetableForm::on_monthComboBox_currentIndexChanged(int index) {
    QDate date = ui->calendarWidget->selectedDate();
    setDate(QDate(date.year(), index + 1, date.day()));
}

void TimetableForm::on_yearComboBox_currentTextChanged(const QString &arg1) {
    QDate date = ui->calendarWidget->selectedDate();
    setDate(QDate(arg1.toInt(), date.month(), date.day()));
}

