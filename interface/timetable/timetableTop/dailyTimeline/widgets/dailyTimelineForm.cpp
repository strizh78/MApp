#include "dailyTimelineForm.h"

#include "appointment/appointment.h"

#include "interface/interfaceUtils.h"
#include "timetable/timetableUtils.h"

#include <QHBoxLayout>

DailyTimelineForm::DailyTimelineForm(QWidget *parent)
    : QWidget(parent)
    , acceptedButton(new QPushButton(this))
    , declinedButton(new QPushButton(this))
    , name_(new ComboBox(this))
    , service_(new ComboBox(this))
    , time_(new ComboBox(this))
{
    auto lay = new QHBoxLayout();
    lay->setContentsMargins(0, 0, 0, 0);

    QString boxesStyleSheet = "border: none;"
                               "background-color: palette(window);"
                               "color: rgb(128, 128, 128);"
                               "border-radius: 20px;"
                               "height: 45px;";

    name_->setStyleSheet(boxesStyleSheet);
    name_->SetAlignment(Qt::AlignCenter);
    name_->setContentsMargins(25, 0, 25, 0);
    service_->setStyleSheet(boxesStyleSheet);
    service_->SetAlignment(Qt::AlignCenter);
    service_->setContentsMargins(25, 0, 25, 0);
    time_->setStyleSheet(boxesStyleSheet);
    time_->SetAlignment(Qt::AlignCenter);
    time_->setContentsMargins(25, 0, 25, 0);

    changeFont(name_, 16, QFont::Normal);
    changeFont(service_, 16, QFont::Normal);
    changeFont(time_, 16, QFont::Normal);

    lay->insertWidget(lay->count(), name_);
    lay->insertWidget(lay->count(), service_);
    lay->insertWidget(lay->count(), time_);

    lay->addStretch();

    QString buttonsStylesheet = "border: none;"
                                "background: transparent;";

    acceptedButton->setStyleSheet(buttonsStylesheet);
    acceptedButton->setIcon(QIcon(":/icons/yesIcon.png"));
    acceptedButton->setFlat(true);

    declinedButton->setStyleSheet(buttonsStylesheet);
    declinedButton->setIcon(QIcon(":/icons/noIcon.png"));
    declinedButton->setFlat(true);

    lay->insertWidget(lay->count(), acceptedButton);
    lay->insertWidget(lay->count(), declinedButton);

    connect(declinedButton, &QPushButton::pressed, this, &QWidget::hide);
    connect(acceptedButton, &QPushButton::pressed, this, &QWidget::hide);

    setLayout(lay);

    setMinimumHeight(45);
    setMaximumHeight(45);
    hide();
}

void DailyTimelineForm::setTimetableEvent(TimetableEvent event) {;
    name_->addItem(event.name);
    name_->setMinimumWidth(name_->fontMetrics().horizontalAdvance(name_->currentText()) + 70);
    name_->update();
    service_->addItem(event.comment);
    service_->setMinimumWidth(service_->fontMetrics().horizontalAdvance(service_->currentText()) + 70);
    service_->update();
    time_->addItem(event.begin.toString("hh:mm") + "-" + event.end.toString("hh:mm"));
    time_->setMinimumWidth(time_->fontMetrics().horizontalAdvance(time_->currentText()) + 70);
    time_->update();
    show();
}
