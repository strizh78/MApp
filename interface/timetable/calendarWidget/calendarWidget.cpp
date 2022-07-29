#include "calendarWidget.h"

#include "interface/interfaceUtils.h"

#include <QGridLayout>
#include <QPainter>
#include <QPushButton>
#include <QStyleOption>

class CalendarDayButton : public  QPushButton {
public:
    CalendarDayButton(QString s, QWidget* parent)
        : QPushButton(s, parent)
    {}

    void setSelected(bool selected) {
        isSelected_ = selected;
    }

protected:
    void paintEvent(QPaintEvent *e) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);

        if (isSelected_) {
            painter.setPen(Qt::transparent);
            painter.setBrush(QColor(136, 79, 207));
            painter.drawEllipse(contentsRect().center(), 19, 19);
        }
        painter.end();

        QPushButton::paintEvent(e);
    }

private:
    bool isSelected_ = false;
};

CalendarWidget::CalendarWidget(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(262);
    setFixedWidth(414);

    auto lay = new QGridLayout();
    lay->setContentsMargins(15, 0, 15, 25);
    lay->setSpacing(0);

    setLayout(lay);
    selectedDate_ = QDate::currentDate();

    updateMonth();
}

QDate CalendarWidget::selectedDate() const {
    return selectedDate_;
}

void CalendarWidget::setSelectedDate(QDate date) {
    bool needUpdate = date.month() != selectedDate_.month() ||
                      date.year() != selectedDate_.year();

    setButtonStyle(selectedDate_, false);

    selectedDate_ = date;
    if (needUpdate) {
        updateMonth();
    }

    setButtonStyle(selectedDate_, true);
}

void CalendarWidget::updateMonth() {
    auto lay = static_cast<QGridLayout*>(layout());
    clearLayout(lay);

    QDate firstDayForMonth = QDate(selectedDate_.year(), selectedDate_.month(), 1);

    while (firstDayForMonth.dayOfWeek() != 1) {
        firstDayForMonth = firstDayForMonth.addDays(-1);
    }

    int rowNumber = 0;
    QDate day = firstDayForMonth;
    for (int i = 0; i < 7; ++i) {

        auto* headerDayOfWeekButton = new QPushButton(day.toString("ddd").toLower(), this);

        QColor color(128, 130, 135);
        if (day.dayOfWeek() > /* friday */ 5) {
            color = QColor(164, 66, 66);
        }

        headerDayOfWeekButton->setStyleSheet("border:none; color: " + color.name());
        headerDayOfWeekButton->setFixedHeight(40);
        headerDayOfWeekButton->setFlat(true);
        changeFont(headerDayOfWeekButton, 16, QFont::Medium);

        lay->addWidget(headerDayOfWeekButton, rowNumber, i);

        day = day.addDays(1);
    }

    rowNumber++;

    QDate lastDayOfMonth = QDate(selectedDate_.year(), selectedDate_.month(), selectedDate_.daysInMonth());
    while (firstDayForMonth <= lastDayOfMonth) {
        for (int i = 0; i < 7; ++i) {
            auto* dayButton = new CalendarDayButton(firstDayForMonth.toString("d"), this);

            dayButton->setObjectName(firstDayForMonth.toString("dd.MM.yyyy"));
            dayButton->setFixedHeight(40);
            dayButton->setFlat(true);
            setButtonStyle(firstDayForMonth, firstDayForMonth == selectedDate_);

            lay->addWidget(dayButton, rowNumber, i);

            connect(dayButton, &QPushButton::clicked, this, &CalendarWidget::calendarDateClicked);

            firstDayForMonth = firstDayForMonth.addDays(1);
        }
        ++rowNumber;
    }

}

void CalendarWidget::calendarDateClicked() {
    auto dateString = QObject::sender()->objectName();

    QDate date = QDate::fromString(dateString, "dd.MM.yyyy");
    setSelectedDate(date);

    emit dateChanged(date);
}

void CalendarWidget::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    painter.setBrush(palette().base().color());
    painter.setPen(palette().base().color());

    auto rect = contentsRect();

    painter.drawRoundedRect(rect, 20, 20);
    painter.drawRect(rect.left(), rect.top(),
                     rect.right(), rect.center().y());
    painter.end();
}

void CalendarWidget::setButtonStyle(QDate date, bool selected) {
    QColor color = palette().text().color();
    if (selected) {
        color = palette().brightText().color();
    } else if (date == QDate::currentDate()) {
        color = QColor(136, 79, 207);
    } else if (date.month() != selectedDate_.month()) {
        color = QColor(174, 175, 180);
    } else if (date.dayOfWeek() > /* friday */ 5) {
        color = QColor(164, 66, 66);
    }

    auto button = findChild<CalendarDayButton*>(date.toString("dd.MM.yyyy"));
    if (button) {

        if (date == QDate::currentDate()) {
            changeFont(button, 18, QFont::DemiBold);
        } else {
            changeFont(button, 18, QFont::Normal);
        }

        button->setStyleSheet("border: none; color: " + color.name());
        button->setSelected(selected);
        button->update();
    }
}
