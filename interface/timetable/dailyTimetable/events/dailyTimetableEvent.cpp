#include "dailyTimetableEvent.h"

#include "interface/timetable/event/eventForm.h"
#include "interface/appointment/appointmentForm.h"

#include "interface/interfaceUtils.h"

#include <QHBoxLayout>
#include <QPainter>

namespace {
    void fixRoundedRectBorderWidth(QPainter& painter, const QRect& rect, int radius, const QColor& color) {
        painter.setPen(QPen(Qt::transparent, 0));
        painter.drawRoundedRect(rect, radius, radius);

        painter.setPen(QPen(color, 1));

        int delta = radius - 5;

        painter.drawLine(QPoint(rect.left(), rect.top() + delta),
                         QPoint(rect.left(), rect.bottom() - delta));
        painter.drawLine(QPoint(rect.right() + 1, rect.top() + delta),
                         QPoint(rect.right() + 1, rect.bottom() - delta));
        painter.drawLine(QPoint(rect.left() + delta, rect.bottom() + 1),
                         QPoint(rect.right() - delta, rect.bottom() + 1));
    }
}

DailyTimetableEvent::DailyTimetableEvent(const TimetableEvent &event, DatabasePtr database, QWidget *parent)
    : QAbstractButton(parent)
    , event_(event)
    , database_(database)
{
    setMouseTracking(true);
    setAttribute(Qt::WA_LayoutUsesWidgetRect);

    auto lay = new QHBoxLayout();
    lay->setContentsMargins(25, 20 + 9, 25, 20);
    setLayout(lay);

    auto label = new QLabel(this);
    label->setGeometry(25, 0, 150, 18);
    label->setAlignment(Qt::AlignmentFlag::AlignCenter);
    changeFont(label, 10, QFont::Normal);
    if (event.type == TimetableEvent::APPOINTMENT) {
        label->setText("<span style=\"color:" + event.color.name() + ";\">медицинский приём</span>");
    } else {
        label->setText("<span style=\"color:" + event.color.name() + ";\">событие</span>");
    }

    auto layLabelsV = new QVBoxLayout();
    layLabelsV->setContentsMargins(0, 10 - 3 + 2, 0, 10 - 3 - 1);
    layLabelsV->setSpacing(20 - 3);

    time_ = new QLabel(event_.begin.toString("h:mm") + " — " + event.end.toString("h:mm"), this);
    changeFont(time_, 18, QFont::Medium, /*italic*/ true);

    name_ = new QLabel(event_.name, this);
    changeFont(name_, 18, QFont::Medium);

    comment_ = new QLabel(event_.comment, this);
    changeFont(comment_, 18, QFont::Normal);
    comment_->setFixedHeight(comment_->fontMetrics().height());
    (comment_->text().isEmpty()) ? comment_->hide() : comment_->show();

    layLabelsV->insertWidget(layLabelsV->count(), time_);
    layLabelsV->insertWidget(layLabelsV->count(), name_);
    layLabelsV->insertWidget(layLabelsV->count(), comment_);

    lay->insertLayout(lay->count(), layLabelsV);

    auto layButtonsV = new QVBoxLayout();
    layButtonsV->setContentsMargins(0, 0, 0, 0);
    layButtonsV->setSpacing(10);

    buttonEdit_ = new QPushButton(this);
    buttonEdit_->setIcon(QIcon(":/icons/editIcon.png"));
    buttonEdit_->setFixedSize(30, 30);
    buttonEdit_->setFlat(true);
    buttonEdit_->setStyleSheet("border: 0;background: transparent;");

    connect(buttonEdit_, &QPushButton::clicked, this, &DailyTimetableEvent::openTimetableEventForm);

    layButtonsV->insertWidget(layButtonsV->count(), buttonEdit_);
    layButtonsV->addStretch();
    lay->insertLayout(lay->count(), layButtonsV);

    setFixedHeight((!comment_->text().isEmpty()) ? 148 + 9 : 112 + 9);
}

void DailyTimetableEvent::setButtonsVisible(bool visible) {
    buttonEdit_->setVisible(visible);
}

void DailyTimetableEvent::update() {
    if (event_.date == QDate::currentDate() &&
        event_.begin <= QTime::currentTime() && event_.end >= QTime::currentTime())
    {
        changeFont(time_, 18, QFont::Bold, /*italic*/ true);
        time_->setStyleSheet("");
    } else {
        changeFont(time_, 18, QFont::Medium, /*italic*/ true);
        time_->setStyleSheet("color:rgb(180, 180, 180);");
    }

    QWidget::update();
}

void DailyTimetableEvent::mouseDoubleClickEvent(QMouseEvent *) {
    openTimetableEventForm();
}

void DailyTimetableEvent::openTimetableEventForm() {
    QWidget* viewForm;

    if (event_.type == TimetableEvent::APPOINTMENT) {
        viewForm = new AppointmentForm(database_, event_.appointment);
    } else {
        viewForm = new EventForm(database_, event_.event);
    }

    viewForm->setAttribute(Qt::WA_DeleteOnClose, true);
    viewForm->show();
}

void DailyTimetableEvent::paintEvent(QPaintEvent *) {
    update();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    auto rect = contentsRect();
    rect.setTop(rect.top() + 9);

    // базовый прямоугольничек и оплеточка
    painter.setPen(QPen(event_.color, 1));
    painter.setBrush(palette().window().color());
    painter.drawRoundedRect(rect, 20, 20);

    // фиксим толщину оплеточки
    fixRoundedRectBorderWidth(painter, rect, 20, event_.color);

    // подпись - прямоугольничек
    painter.setPen(QPen(event_.color, 1));
    painter.setBrush(palette().base().color());
    QRect miniRect(rect.left() + 25, rect.top() - 9, 150, 18);
    painter.drawRoundedRect(miniRect, 9, 9);
    painter.setPen(QPen(Qt::transparent, 0));
    painter.drawRoundedRect(miniRect, 9, 9);

    painter.setPen(palette().base().color());
    painter.drawRect(miniRect.left(), miniRect.top(), miniRect.width(), 8);

    setButtonsVisible(underMouse());
}
