#include "dailyTimetable.h"

#include "interface/appointment/appointmentForm.h"
#include "interface/timetable/event/eventForm.h"

#include "interface/utils.h"
#include "timetable/timetableUtils.h"

#include <QTime>
#include <QMouseEvent>

DailyTimetable::DailyTimetable(QWidget *parent)
    : QWidget(parent)
    , date_(QDate::currentDate())
{

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(30);

    setMinimumHeight(drawSettings_.startYCoordinate + drawSettings_.oneHourHeight * drawSettings_.timetableHoursCount);
}

void DailyTimetable::setDate(QDate date) {
    date_ = date;
}

void DailyTimetable::setDatabase(std::shared_ptr<DatabaseInterface> database) {
    database_ = database;
}

void DailyTimetable::update() {
    updateData();
    QWidget::update();
}

void DailyTimetable::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);
    updateData();
    updatePainting();
}

void DailyTimetable::updateData() {
    timetableEntries_.clear();

    std::vector<Appointment> appointments;
    database_->appointment->list(appointments);
    addEntries(appointments);

    std::vector<Event> events;
    database_->event->list(events);
    addEntries(events);
}

template <class EntryBase>
void DailyTimetable::addEntries(std::vector<EntryBase> data) {
    for (const auto& x : data) {
        if (x.isDeleted() == false) {
            timetableEntries_.insert(getEntry(x, drawSettings_));
        }
    }
}

void DailyTimetable::updatePainting() {
    drawSettings_.width = width();

    QPainter painter(this);

    // background
    int height = drawSettings_.startYCoordinate + drawSettings_.oneHourHeight * drawSettings_.timetableHoursCount;
    painter.fillRect(QRect(0 /*startW*/, 0 /*startH*/, width(), height), palette().base());

    QTime time(drawSettings_.firstTimetableHour, 0);
    for (int i = 0; i < drawSettings_.timetableHoursCount; ++i) {
        drawTimeLine(painter, time, palette().text().color());
        time = time.addSecs(/*1 hour*/ 60 * 60);
    }

    // events
    for (auto& x : timetableEntries_) {
        if (x->isDateEquals(date_)) {
            x->draw(painter);
        }
    }

    drawTimeLine(painter, QTime::currentTime(), Qt::red, true);

    QFont f;
    f.setBold(true);
    f.setPointSize(fontInfo().pointSize() + 10);
    painter.setFont(f);
    int x = fontInfo().pointSize() + 13;
    painter.drawText(QRect(0 + 5, 0 + 5, width(), x), Qt::AlignLeft | Qt::AlignVCenter, date_.toString("d MMMM yyyy г."));
    f.setPointSize(fontInfo().pointSize() + 7);
    painter.setFont(f);
    painter.drawText(QRect(0 + 5, x, width(), drawSettings_.startYCoordinate / 2), Qt::AlignLeft | Qt::AlignVCenter, date_.toString("dddd"));
}

void DailyTimetable::drawTimeLine(QPainter & painter, QTime time, QColor color, bool needCircleMarker) {
    QPen savedPen = painter.pen();

    color.setAlphaF(0.5);
    painter.setPen(QPen(color));

    int hoursDelta = time.hour() - drawSettings_.firstTimetableHour;
    int timeY = drawSettings_.startYCoordinate + drawSettings_.oneHourHeight * hoursDelta + drawSettings_.oneHourHeight * (time.minute() / 60.);
    painter.drawLine(QPointF(drawSettings_.startXCoordinate, timeY), QPointF(width(), timeY));
    painter.drawText(QPointF(0 + 5, timeY + 4), time.toString("hh:mm"));

    if (needCircleMarker) {
        color.setAlphaF(1);
        painter.setBrush(color);
        painter.drawEllipse(QPointF(drawSettings_.startXCoordinate + 1.5, timeY), 3, 3);
    }

    painter.setPen(savedPen);
}

QTime getTime(const QPoint& point, const TimetableDrawSettings& settings) {
    int hour = ((point.y() - settings.startYCoordinate) / settings.oneHourHeight + settings.firstTimetableHour) % 24;
    QTime time(hour, 0);

    int minutes = ((point.y() - settings.startYCoordinate) % settings.oneHourHeight) % 60;
    std::vector <int> patternMins = {0, 15, 30, 45, 60};
    std::vector <int> clickedMins = {8, 23, 38, 53, 60};

    for (size_t i = 0; i < clickedMins.size(); ++i) {
        if (minutes < clickedMins[i]) {
            minutes = patternMins[i];
            break;
        }
    }

    time = time.addSecs(60 * minutes);
    return time;
}

void DailyTimetable::mouseDoubleClickEvent(QMouseEvent *event) {
    for (const auto& x : timetableEntries_) {
        if (x->rectContainsPoint(event->pos()) && x->isDateEquals(date_)) {
            x->openForm(database_, this);
            return;
        }
    }

    Appointment newAppointment;
    newAppointment.date.setDate(date_);
    newAppointment.date.setTime(getTime(event->pos(), drawSettings_));
    auto * appointmentViewForm = new AppointmentForm(database_, newAppointment);
    connect(appointmentViewForm, SIGNAL(appointmentCreateSignal(Appointment)),
            this, SLOT(update()));

    showAsWindowModal(appointmentViewForm);
}

void DailyTimetable::mousePressEvent(QMouseEvent *event) {
    lastMovePosition_ = event->pos();
}

void DailyTimetable::mouseMoveEvent(QMouseEvent *event) {
    const int minHour = drawSettings_.firstTimetableHour;
    const int maxHour = minHour + drawSettings_.timetableHoursCount;

    for (const auto& x : timetableEntries_) {
        if (x->rectContainsPoint(lastMovePosition_) && x->isDateEquals(date_)) {
            QTime currentClick = getTime(event->pos(), drawSettings_);

            QTime delta = currentClick.addSecs(-toSeconds(getTime(lastMovePosition_, drawSettings_)));
            if (delta.hour() + delta.minute() != 0 &&
                x->tryMoveEntry(delta, database_, minHour, maxHour))
            {
                lastMovePosition_ = event->pos();
                update();
            }
            return;
        }
    }
}
